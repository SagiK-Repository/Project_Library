using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using Akka.Actor;
using OfficeOpenXml;
using ExcelPackage = OfficeOpenXml.ExcelPackage;
using System.Threading;

namespace FileTransferComparison
{
    public static class Program
    {
        private static void Main()
        {
            Init();
            IActorRef senderActor = InitActor();

            LaunchAkkaVsFTP(senderActor);

            ExcelService.Save();

            Console.ReadLine();
        }
        
        private static void LaunchAkkaVsFTP(IActorRef actorRef)
        {

            for (int size = 1; size < 10000; size++)
                ImageService.UseImage(size, (imageFilePath) =>
                {
                    Console.WriteLine($"============================================== Start Image {size}");

                    RepeatAkkaFile(actorRef, size, "./" + imageFilePath);
                    RepeatFTPFile(size, imageFilePath);

                    ExcelService.Save();

                    Console.WriteLine($"============================================== End Image {size}");

                    if (size % 1000 == 0)
                    {
                        Console.WriteLine($"Save Excel {size}");
                        ExcelService.Save();
                    }
                });
        }

        private static void RepeatAkkaFile(IActorRef actorRef, int size, string imageFilePath)
        {
            for(int repeatNum = 0; repeatNum < 10;  repeatNum++)
            {
                actorRef.Tell(new SendMessage(middleName : $"[Akka_{size}_{repeatNum}]", filePath : imageFilePath, x : repeatNum + 3, y : size));
            }
        }

        private static void RepeatFTPFile(int size, string imageFilePath)
        {
            List<TimeSpan> timeSpans = new List<TimeSpan>();

            for (int repeatNum = 0; repeatNum < 10; repeatNum++)
                timeSpans.Add(FTPService.DownloadFileTime(imageFilePath));

            double averageTicks = timeSpans.Average(time => time.Ticks);
            TimeSpan averageTimeSpan = TimeSpan.FromTicks((long)averageTicks);

            ExcelService.AddValue(averageTimeSpan.ToString(), 1, size);
        }

        private static IActorRef InitActor()
        {
            var actorSystem = ActorSystem.Create("FileTransferSystem");
            var receiveActor = actorSystem.ActorOf<FileReceiverActor>("FileReceiver");
            return actorSystem.ActorOf(Props.Create(() => new FileSenderActor(receiveActor)), "FileSender");
        }

        public static void Init()
        {
            ExcelService.Init();
            FTPService.InitializeFTP();
        }
    }

    #region Actor
    public class SendMessage
    {
        public string MiddleName { get; }
        public string FilePath { get; }
        public int X { get; }
        public int Y { get; }
        public (int, int) Position => (X, Y);

        public SendMessage(string middleName, string filePath, int x, int y)
        {
            MiddleName = middleName;
            FilePath = filePath;
            X = x;
            Y = y;
        }
    }

    public class FileMessage
    {
        public byte[] FileData { get; }
        public DateTime StartTime { get; }
        public (int X, int Y) Position { get; }
        public string MiddleName { get; }

        public FileMessage(byte[] fileData , DateTime startTime, (int, int) position, string middleName)
        {
            FileData = fileData;
            StartTime = startTime;
            Position = position;
            MiddleName = middleName;
        }
    }

    public class FileReceiverActor : ReceiveActor
    {
        public FileReceiverActor()
        {
            Receive<FileMessage>(message =>
            {
                string randomName = Guid.NewGuid().ToString();
                string filePath = Path.Combine(Directory.GetCurrentDirectory(), randomName);

                using (var fileStream = new FileStream(filePath, FileMode.Create))
                {
                    fileStream.Write(message.FileData, 0, message.FileData.Length);
                }

                TimeSpan time = DateTime.Now - message.StartTime;

                ExcelService.AddValue(time.ToString(), message.Position.X, message.Position.Y);
                Console.WriteLine($"Akka : Download End [{message.Position.X}][{message.Position.Y}] {message.MiddleName} : {filePath}");
                File.Delete(filePath);
            });
        }
    }

    public class FileSenderActor : ReceiveActor
    {
        private IActorRef _receiver;

        public FileSenderActor(IActorRef receiver)
        {
            _receiver = receiver;

            Receive<SendMessage>(message =>
            {
                Console.WriteLine($"Akka : Start [{message.X}][{message.Y}] {message.MiddleName} : {message.FilePath}");
                DateTime startDate = DateTime.Now;

                if (File.Exists(message.FilePath))
                {
                    byte[] fileData = File.ReadAllBytes(message.FilePath);
                    var fileMessage = new FileMessage(fileData, startDate, message.Position, message.MiddleName);
                    _receiver.Tell(fileMessage);
                }
                else
                {
                    Console.WriteLine($"File not found: {message.FilePath}");
                }
            });
        }
    }
    #endregion

    #region Excel
    public static class ExcelService
    {
        private static string _filePath = "transfer_times.xlsx";
        private static string _sheetName = "Data";
        private static ExcelPackage excelPackage = null;
        private static OfficeOpenXml.ExcelWorksheet excelWorksheet = null;

        public static void Init()
        {
            ExcelPackage.LicenseContext = LicenseContext.NonCommercial; // 비상업적 용도로 사용
            excelPackage = new ExcelPackage(new FileInfo(_filePath));

            if (excelPackage.Workbook.Worksheets[_sheetName] == null)
                excelWorksheet = excelPackage.Workbook.Worksheets.Add(_sheetName);
            else
                excelWorksheet = excelPackage.Workbook.Worksheets[_sheetName];
        }

        public static void AddValue(string value, int row, int column)
        {
            excelWorksheet.Cells[row, column].Value = value;
        }

        public static void Save()
        {
            excelPackage.Save();
        }
    }
    #endregion

    #region Image
    public static class ImageService
    {
        private static string _fileName = "Image";
        private static string _sourceImagePath = $"./{_fileName}.jpg";
        private static Bitmap _sourceImage = new Bitmap(_sourceImagePath);

        public static void UseImage(int size, Action<string> action)
        {
            string saveFileName = SaveImage(size);
            action(saveFileName);
            try { File.Delete("./" + saveFileName); } catch(Exception) { Thread.Sleep(100); File.Delete("./" + saveFileName); }
            try { File.Delete("D:\\FTP_Folder\\" + saveFileName); } catch (Exception) { Thread.Sleep(100); File.Delete("D:\\FTP_Folder\\" + saveFileName); }
        }

        public static string SaveImage(int size)
        {
            string fileName = $"{_fileName}{size}.jpg";
            _resizeAndSaveImage(fileName, size, size);
            return fileName;
        }
        private static void _resizeAndSaveImage(string fileName, int width, int height)
        {
            try
            {
                using (var resizedImage = new Bitmap(width, height))
                using (var graphics = Graphics.FromImage(resizedImage))
                {
                    graphics.DrawImage(_sourceImage, 0, 0, width, height);
                    resizedImage.Save("./" + fileName);
                }
                File.Copy("./" + fileName, "D:\\FTP_Folder\\" + fileName);
                Console.WriteLine("Image resized and saved successfully.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error resizing and saving image: {ex.Message}");
            }
        }
    }
    #endregion

    #region FTP
    public static class FTPService
    {
        private static string _ftpServerUrl = "192.168.162.1";
        private static string _id = "ftps";
        private static string _password = "ftps";
        private static WebClient _webClient = new WebClient();

        public static void InitializeFTP()
        {
            try
            {
                _webClient.Credentials = new NetworkCredential(_id, _password);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error downloading file: {ex.Message}");
            }
        }

        public static TimeSpan DownloadFileTime(string filePath)
        {
            Console.WriteLine($"FTP : Start Download {filePath}");
            
            var stopwatch = Stopwatch.StartNew();

            string savePath = _downloadFileFromFtp(filePath);
            stopwatch.Stop();
            
            Console.WriteLine($"FTP : End Download [{stopwatch.Elapsed}] {filePath}");
            File.Delete(savePath);

            return stopwatch.Elapsed;
        }

        private static string _downloadFileFromFtp(string filePath)
        {
            string localFilePath = ".\\" + Path.GetFileName(filePath);
            string randomName = Guid.NewGuid().ToString();
            string fileName = localFilePath + randomName + ".jpg";
            _webClient.DownloadFile($"ftp://{_ftpServerUrl}/{filePath}", fileName);

            return fileName;
        }
    }
    #endregion
}


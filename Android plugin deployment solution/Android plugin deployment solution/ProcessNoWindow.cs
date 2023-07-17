using System.Diagnostics;

namespace fastman92
{
    class ProcessNoWindow
    {

        public Process process;

        DataReceivedEventHandler dataReceivedHandler;

        public void Init(DataReceivedEventHandler dataReceivedHandler)
        {
            this.dataReceivedHandler = dataReceivedHandler;
        }

        public void StartAndWaitForExit(string FileName, string Arguments)
        {
            process = new Process();

            process.StartInfo.CreateNoWindow = true;
            process.StartInfo.UseShellExecute = false;

            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.RedirectStandardError = true;

            process.OutputDataReceived += this.dataReceivedHandler;
            process.ErrorDataReceived += this.dataReceivedHandler;

            process.StartInfo.FileName = FileName;
            process.StartInfo.Arguments = Arguments;

            process.Start();

            process.BeginOutputReadLine();
            process.BeginErrorReadLine();

            process.WaitForExit();
        }
    };
}
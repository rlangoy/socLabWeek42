using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Threading;     //Add threading support
using System.Net;           //Add network support
using System.Net.Sockets;   //Add Sockets support


namespace UDP_RECIEVE
{
    public partial class Form1 : Form
    {
        public string strRecievedUDPMessage;
        public void DoReciveUDP()
        {
            UdpClient sock = new UdpClient(9050);
            IPEndPoint iep = new IPEndPoint(IPAddress.Any, 0);

            while (true)
            {
                try
                {   //Recieve message as UDP
                    byte[] data = sock.Receive(ref iep);
                    //Convert Bytes to a ASCII String
                    strRecievedUDPMessage =
                        Encoding.ASCII.GetString(data, 0, data.Length);
                    //Cal the function UdpDataRecieved
                    this.Invoke(new EventHandler(this.UdpDataRecieved));
                }
                catch (Exception e) { }
            }
            sock.Close();
        }

        //This is only called by DoReciveUDP
        public void UdpDataRecieved(object sender, EventArgs e)
        {   //Show the message in the form
            textBox1.Text = strRecievedUDPMessage;
        }
        
        
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {   Thread workerThread = new Thread(this.DoReciveUDP);
            // Start the worker thread.
            workerThread.Start();
        }



    }
}

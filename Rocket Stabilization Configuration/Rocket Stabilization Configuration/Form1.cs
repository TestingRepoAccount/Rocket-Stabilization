using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Rocket_Stabilization_Configuration
{
    public partial class RocketConfig : Form
    {
        static SerialPort serialPort1;

        public RocketConfig()
        {
            InitializeComponent();
            getAvailablePorts();
            serialPort1 = new SerialPort();
        }


        private void RocketConfig_Load(object sender, EventArgs e)
        {

        }

        void getAvailablePorts()
        {
            Ports_Box.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            Ports_Box.Items.AddRange(ports);

        }


    }
}


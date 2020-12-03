using RGiesecke.DllExport;
using System.Windows.Forms;

namespace CS_DllMain
{
    public class Main
    {

        [DllExport]
        public static void CS_DllMain()
        {
            MessageBox.Show("Bonjour from .NET Framework 4 :O");
            // Don't forget to run almost everything in a thread (avoid ui blocking) !
        }

    }
}


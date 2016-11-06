using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectEditor.src.Model
{
    public class Animation
    {
        public Animation()
        {
        }

        public Animation(string pName, int pBeginFrame, int pEndFrame)
        {
            Name = pName;
            BeginFrame = pBeginFrame;
            EndFrame = pEndFrame;
        }

        public string Name { get; set; } = "Default";

        public int BeginFrame { get; set; } = 1;

        public int EndFrame { get; set; } = 1;

        public override string ToString()
        {
            return Name + " [" + BeginFrame + " - " + EndFrame + "]";
        }
    }
}

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
        const string c_generalCat = "General";


        public Animation()
        {
        }

        public Animation(string pName, int pBeginFrame, int pEndFrame, float pInterval)
        {
            Name = pName;
            BeginFrame = pBeginFrame;
            EndFrame = pEndFrame;
            Interval = pInterval;
        }


        [Category(c_generalCat)]
        [Description("Name of the animation")]
        public string Name { get; set; } = "Default";

        [Category(c_generalCat)]
        [Description("The first frame of the animation")]
        public int BeginFrame { get; set; } = 1;

        [Category(c_generalCat)]
        [Description("The last frame of the animation")]
        public int EndFrame { get; set; } = 1;

        [Category(c_generalCat)]
        [Description("Interval between frame change, seconds")]
        public float Interval { get; set; } = 0.5f;

        public override string ToString()
        {
            return Name + " [" + BeginFrame + " - " + EndFrame + "]";
        }
    }
}

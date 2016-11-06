using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace ObjectEditor.src.Model
{
    public class TextureContainer
    {
        const string c_generalCat = "General";


        [Category(c_generalCat)]
        [Description("Name of the texture")]
        public string Name { get; set; } = "";


        [Category(c_generalCat)]
        [Description("Width of the single frame of the texture.")]
        public int Width { get; set; } = -1;

        [Category(c_generalCat)]
        [Description("Height of the single frame of the texture.")]
        public int Height { get; set; } = -1;

        [Category(c_generalCat)]
        [Description("Number of frames in the texture.")]
        public int NumberOfFrames { get; set; } = -1;

        [Category(c_generalCat)]
        [Description("Indicates whether the alpha check should be performed for this texture.")]
        public bool CheckAlpha { get; set; } = false;


        [Category(c_generalCat)]
        [ReadOnly(true)]
        [Description("Texture file extension.")]
        public string Extension { get; set; } = "";


        [XmlIgnore]
        [Browsable(false)]
        public string RealFileName = "";

        public override string ToString()
        {
            if (IsCorrectFormat())
                return Name + "_" + Width + "_" + Height + "_" + NumberOfFrames + "_" + (CheckAlpha ? "a" : "n") + Extension;
            else
                return Name;
        }

        public bool IsCorrectFormat()
        {
            return (!string.IsNullOrEmpty(Name) && Width != -1 && Height != -1 && NumberOfFrames != -1);
        }
    }
}

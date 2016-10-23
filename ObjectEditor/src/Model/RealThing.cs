using ObjectEditor.src.Controller;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Xml.Serialization;

namespace ObjectEditor.src.Model
{
    public class RealThing
    {

        const string c_generalCategory = "General";
        const string c_textureCategory = "Texture";
        const string c_physicsProperties = "Physical properties";


        public RealThing()
        {
        }

        public RealThing(string pTypeName)
        {
            if (string.IsNullOrEmpty(pTypeName))
                throw new Exception("Empty RealThing.TypeName provided.");

            TypeName = pTypeName;
        }


        [ReadOnly(true)]
        [Description("Name of the thing type (eg. \"Table\" or \"Door\"). Can be chaged via the tree view on the left.")]
        [Category(c_generalCategory)]
        public string TypeName { get; set; }



        [Browsable(false)]
        [XmlIgnore]
        public TextureContainer Texture { get; set; } = new TextureContainer();

        [Description("Path to the texture.")]
        [Category(c_textureCategory)]
        [Editor(typeof(System.Windows.Forms.Design.FileNameEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public string TextureFilePath
        {
            get { return Texture.FileName; }
            set { Texture.FileName = Path.IsPathRooted(value) ? Utils.MakeRelativePath(Directory.GetCurrentDirectory() + "\\Textures\\", value) : value; }
        }

        [ReadOnly(true)]
        [Description("Width of the texture.")]
        [Category(c_textureCategory)]
        [XmlIgnore]
        public int TextureWidth
        {
            get { return Texture.Width; }
            set { Texture.Width = value; }
        }

        [ReadOnly(true)]
        [Description("Height of the texture.")]
        [Category(c_textureCategory)]
        [XmlIgnore]
        public int TextureHeight
        {
            get { return Texture.Height; }
            set { Texture.Height = value; }
        }

        [ReadOnly(true)]
        [Description("Number of frames in the texture.")]
        [Category(c_textureCategory)]
        [XmlIgnore]
        public int TextureFramesCount
        {
            get { return Texture.NumberOfFrames; }
            set { Texture.NumberOfFrames = value; }
        }



        [Description("Indicates whether the large creature (like human) can pass through this thing.")]
        [Category(c_physicsProperties)]
        public bool IsPassable { get; set; } = true;

        [Description("Indicates whether the gas can pass through this thing.")]
        [Category(c_physicsProperties)]
        public bool IsVentilated { get; set; } = true;
    }
}

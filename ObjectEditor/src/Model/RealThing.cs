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

        const string c_generalCat = "General";
        const string c_textureCat = "Texture";
        const string c_physicsCat = "Physical properties";
        const string c_constructionCat = "Construction";


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
        [Category(c_generalCat)]
        public string TypeName { get; set; }



        [Browsable(false)]
        [XmlIgnore]
        public TextureContainer Texture { get; set; } = new TextureContainer();

        [Description("Path to the texture.")]
        [Category(c_textureCat)]
        [Editor(typeof(System.Windows.Forms.Design.FileNameEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public string TextureFilePath
        {
            get { return Texture.FileName; }
            set { Texture.FileName = Path.IsPathRooted(value) ? Utils.MakeRelativePath(Directory.GetCurrentDirectory() + "\\Textures\\", value) : value; }
        }

        [ReadOnly(true)]
        [Description("Width of the texture.")]
        [Category(c_textureCat)]
        [XmlIgnore]
        public int TextureWidth
        {
            get { return Texture.Width; }
            set { Texture.Width = value; }
        }

        [ReadOnly(true)]
        [Description("Height of the texture.")]
        [Category(c_textureCat)]
        [XmlIgnore]
        public int TextureHeight
        {
            get { return Texture.Height; }
            set { Texture.Height = value; }
        }

        [ReadOnly(true)]
        [Description("Number of frames in the texture.")]
        [Category(c_textureCat)]
        [XmlIgnore]
        public int TextureFramesCount
        {
            get { return Texture.NumberOfFrames; }
            set { Texture.NumberOfFrames = value; }
        }



        [Description("Indicates whether the large creature (like human) can pass through this thing.")]
        [Category(c_physicsCat)]
        public bool IsPassable { get; set; } = true;

        [Description("Indicates whether the gas can pass through this thing.")]
        [Category(c_physicsCat)]
        public bool IsVentilated { get; set; } = true;


        [Description("Does this thing requires lattice as a basement")]
        [Category(c_constructionCat)]
        public bool NeedsLattice { get; set; } = true;

        [Description("Does this thing requires floor as a basement")]
        [Category(c_constructionCat)]
        public bool NeedsFloor { get; set; } = true;

        [Description("Does this thing can be built only in the open space")]
        [Category(c_constructionCat)]
        public bool NeedsSpace { get; set; } = true;
    }
}

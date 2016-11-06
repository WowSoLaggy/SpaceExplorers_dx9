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
        const string c_behaviourCat = "Behaviour";
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


        [Category(c_textureCat)]
        [Description("Texture of the thing.")]
        [Editor(typeof(TexturePickerUiEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public TextureContainer Texture { get; set; } = new TextureContainer();

        [Browsable(false)]
        public string TextureFileName { get { return Texture.ToString(); }  set { } }


        [Description("Indicates whether the large creature (like human) can pass through this thing.")]
        [Category(c_physicsCat)]
        public bool IsPassable { get; set; } = true;

        [Description("Indicates whether the gas can pass through this thing.")]
        [Category(c_physicsCat)]
        public bool IsVentilated { get; set; } = true;


        [Description("Does this thing requires lattice as a basement")]
        [Category(c_constructionCat)]
        public bool NeedsLattice { get; set; } = false;

        [Description("Does this thing requires floor as a basement")]
        [Category(c_constructionCat)]
        public bool NeedsFloor { get; set; } = false;

        [Description("Does this thing can be built only in the open space")]
        [Category(c_constructionCat)]
        public bool NeedsSpace { get; set; } = false;

        [Description("Does this thing require any surface to be built (floor, table, ...)")]
        [Category(c_constructionCat)]
        public bool NeedsSurface { get; set; } = true;


        [Description("Behaviour preset")]
        [Category(c_behaviourCat)]
        public ThingBehaviours Behaviour { get; set; } = ThingBehaviours.None;
    }
}

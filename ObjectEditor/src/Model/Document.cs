using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace ObjectEditor.src.Model
{

    [XmlRootAttribute("Document")]
    public class Document
    {
        public Document() { }

        public Document(string pFileName)
        {
            FileName = pFileName;
        }

        public string FileName;

        [XmlArray("Things")]
        [XmlArrayItem("Thing")]
        public List<RealThing> Things = new List<RealThing>();

        [XmlIgnore]
        public bool Changed = true;
    }
}

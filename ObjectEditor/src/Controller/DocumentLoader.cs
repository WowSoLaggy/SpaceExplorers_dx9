using System;
using ObjectEditor.src.Model;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;

namespace ObjectEditor.src.Controller
{
    static class DocumentSaverLoader
    {

        static public void Save(Document pDocument)
        {
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(Document));
            TextWriter textWriter = new StreamWriter(pDocument.FileName);
            xmlSerializer.Serialize(textWriter, pDocument);
            textWriter.Close();

            pDocument.Changed = false;
        }


        static public Document Load(string pFilePath)
        {
            if (!File.Exists(pFilePath))
                return null;


            XmlSerializer xmlSerializer = new XmlSerializer(typeof(Document));
            TextReader textReader = new StreamReader(pFilePath);
            Document document = (Document)xmlSerializer.Deserialize(textReader);
            textReader.Close();


            document.Changed = false;
            return document;
        }
    }
}

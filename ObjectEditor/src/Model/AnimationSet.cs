using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace ObjectEditor.src.Model
{
    public class AnimationSet
    {
        private List<Animation> m_animations = new List<Animation>();

        [XmlElement("Animation")]
        public List<Animation> Animations { get { return m_animations; } }

        [XmlIgnore]
        public int Count { get { return m_animations.Count; } }

        public override string ToString()
        {
            string res = "";
            foreach (var animName in m_animations)
                res += animName + " ";
            return res;
        }
    }
}

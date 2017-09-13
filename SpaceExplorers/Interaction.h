#pragma once


namespace Model
{
class GameObject;
} // ns Model


namespace Controller
{

class Interaction
{
public:

  static bool interact(Model::GameObject* i_object,
                       Model::GameObject* i_subject);
};

} // ns Controller

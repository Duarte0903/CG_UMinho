#include <list>
#include <string>
#include "ponto.hpp"
#ifndef GROUPS_HPP
#define GROUPS_HPP


typedef struct group* Group;

typedef struct transform* Transform;

typedef enum class TransformType;

Group novoGrupo();

Group getChild(Group g, int i);
std::list<Transform> getTransform(Group g);
std::list<void*> getFiles(Group g);
void add_transform(Group node, std::list<Transform> transfrom_node);
void add_node(Group node, Group child_node);
void push_file(Group group, void* file);

Transform novoTransform();

void add_transformType(Transform t, const char* type);
const char* get_transformType(Transform t);
void add_transformAngle(Transform t, float angle);
float get_transformAngle(Transform t);
void add_transformX(Transform t, float x);
void add_transformY(Transform t, float y);
void add_transformZ(Transform t, float z);
float get_transformX(Transform t);
float get_transformY(Transform t);
float get_transformZ(Transform t);
void add_time(Transform t, float time);
void add_align(Transform t, const char* align);
float get_time(Transform t);
bool get_align(Transform t);
void add_pontosCat(Transform t, std::list<Ponto> pontos);
std::list<Ponto> get_pontosCat(Transform t);
void add_pontosControlCat(Transform t, std::list<Ponto> pontos);
std::list<Ponto> get_pontosControlCat(Transform t);

#endif
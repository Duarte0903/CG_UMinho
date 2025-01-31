#include "ponto.hpp"
#include "groups.hpp"
#include "colors.hpp"
#include <list>
#include <string> 
#ifndef FIGURA_HPP
#define FIGURA_HPP

typedef struct figura* Figura;

void setTypeFig(Figura f, std::string type);

std::string getTypeFig(Figura f);

bool getCurva(Figura f);

void setCurva(Figura f, bool curva);

void addPontosControlFigura(Figura f, std::list<Ponto> pontosControl);

std::list<Ponto> getPontosControlFigura(Figura f);

std::list<Ponto> getPontos(Figura f);

Figura novaFigura();

void adicionarPonto(Figura f, const Ponto novoPonto);

void adicionarVariosPontos(Figura f, Figura f2);

void add_color(Figura f, Color c);

Color get_color(Figura f);

void add_texture(Figura f, const char* file);

void criarFile(const Figura f, const char* path, const char* type);

Figura criarFigura(const char* path);

void apagarFigura(Figura f);

std::list<Figura> criarListaFiguras(Group group, int elapsedTime, int instantBefore);

void applyTransforms(std::list<Figura>& figuras, std::list<Transform>& transforms, int elapsedTime, int instantBefore);

void applyScalesToTransforms(std::list<Transform>& transforms);

#endif
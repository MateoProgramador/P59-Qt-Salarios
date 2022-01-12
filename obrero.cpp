#include "obrero.h"

Obrero::Obrero(QObject *parent) : QObject(parent)
{
    this->m_nombre = "";
    this->m_horas = 0;
    this->m_jornada = TipoJornada::Matutina;
}

const QString &Obrero::nombre() const
{
    return m_nombre;
}

void Obrero::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

int Obrero::horas() const
{
    return m_horas;
}

void Obrero::setHoras(int newHoras)
{
    m_horas = newHoras;
}

TipoJornada Obrero::jornada() const
{
    return m_jornada;
}

void Obrero::setJornada(TipoJornada newJornada)
{
    m_jornada = newJornada;
}

Obrero::Obrero(const QString &nombre, int horas, TipoJornada jornada) : m_nombre(nombre),
    m_horas(horas),
    m_jornada(jornada)
{}

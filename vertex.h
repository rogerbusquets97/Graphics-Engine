#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

struct Vertex {
  QVector3D Position;
  QVector3D Normal;
  QVector2D TexCoords;
  QVector3D Tangent;
  QVector3D Bitangent;
};



#endif // VERTEX_H

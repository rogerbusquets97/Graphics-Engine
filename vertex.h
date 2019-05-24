#ifndef VERTEX_H
#define VERTEX_H

#define MAX_VERTEX_ATTRIBUTES 5

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:

    void setVertexAttribute(int location, int offset, int ncomp)
    {
       attribute[location].enabled = true;
       attribute[location].offset = offset;
       attribute[location].ncomp = ncomp;
       size += ncomp * sizeof(float);

    }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

#endif // VERTEX_H

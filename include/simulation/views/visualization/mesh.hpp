#pragma once

#include <vector>

#include <glad/glad.h>

#include "vertex.hpp"


class Mesh {
public:
    enum Type {
        Triangles = GL_TRIANGLES,
        Lines = GL_LINES,
        LinesStrip = GL_LINE_STRIP,
        Patches = GL_PATCHES
    };

    enum Usage {
        Static = GL_STATIC_DRAW,
        Dynamic = GL_DYNAMIC_DRAW,
    };

    Mesh();
    Mesh(Mesh&& mesh) = default;
    Mesh(Mesh& mesh) = delete;
    ~Mesh();

    template <Vertex v, class Allocator>
    void Update(
        const std::vector<v, Allocator>& vertices,
        const std::vector<uint32_t>& indices,
        const Type meshType = Triangles,
        const Usage usage = Static
    ) {
        Use();

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v) * vertices.size(), vertices.data(), usage);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), usage);

        v::SetupAttributes();

        type = meshType;
        elementsCnt = indices.size();
    }

    template <Vertex v, class Allocator>
    void UpdateSomeVertices(const std::vector<v, Allocator>& vertices, const size_t startingIndex, const size_t elemsToUpdate)
    {
        Use();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, startingIndex*sizeof(v), sizeof(v) * elemsToUpdate, vertices.data() + startingIndex);
    }


    [[nodiscard]]
    size_t GetElementsCnt() const
        { return elementsCnt; }

    void Use() const
        { glBindVertexArray(VAO); }


    [[nodiscard]]
    Type GetType() const
        { return type; }

    Mesh& operator=(Mesh& mesh) = delete;

private:
    /// @brief OpenGl vector array object
    unsigned int VAO = 0;

    /// @brief OpenGl vector buffer object
    unsigned int VBO = 0;

    /// @brief OpenGl element buffer object
    unsigned int EBO = 0;

    Type type = Triangles;
    size_t elementsCnt = 0;
};

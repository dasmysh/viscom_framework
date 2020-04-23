/**
 * @file   Vertices.h
 * @author Sebastian Maisch <sebastian.maisch@uni-ulm.de>
 * @date   2016.11.30
 *
 * @brief  Defines all vertices used in the application.
 */

#pragma once

#include <glm/glm.hpp>

namespace viscom {

    class GPUProgram;
    class Mesh;

    struct SimpleVertex
    {
        glm::vec3 position_;

        SimpleVertex(const glm::vec3& pos) : position_(pos) {}
    };

    struct GridVertex
    {
        glm::vec3 position_;
        glm::vec4 color_;

        GridVertex(const glm::vec3& pos, const glm::vec4& col) : position_(pos), color_(col) {}
    };

    struct SimpleMeshVertex
    {
        glm::vec3 position_;
        glm::vec3 normal_;
        glm::vec2 texCoords_;

        SimpleMeshVertex() : position_(0.0f), normal_(0.0f), texCoords_(0.0f) {}
        SimpleMeshVertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex) : position_(pos), normal_(normal), texCoords_(tex) {}
        static void SetVertexAttributes(const GPUProgram* program)
        {
            auto attribLoc = program->GetAttributeLocations({ "position", "normal", "texCoords" });

            if (attribLoc[0] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[0]);
                gl::glVertexAttribPointer(attribLoc[0], 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(SimpleMeshVertex), reinterpret_cast<GLvoid*>(offsetof(SimpleMeshVertex, position_)));
            }
            if (attribLoc[1] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[1]);
                gl::glVertexAttribPointer(attribLoc[1], 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(SimpleMeshVertex), reinterpret_cast<GLvoid*>(offsetof(SimpleMeshVertex, normal_)));
            }
            if (attribLoc[2] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[2]);
                gl::glVertexAttribPointer(attribLoc[2], 2, gl::GL_FLOAT, gl::GL_FALSE, sizeof(SimpleMeshVertex), reinterpret_cast<GLvoid*>(offsetof(SimpleMeshVertex, texCoords_)));
            }
        }

        static GLuint CreateVertexBuffer(const Mesh* mesh)
        {
            GLuint vbo = 0;
            gl::glGenBuffers(1, &vbo);
            std::vector<SimpleMeshVertex> bufferMem(mesh->GetVertices().size());
            for (std::size_t i = 0; i < mesh->GetVertices().size(); ++i) {
                bufferMem[i].position_ = mesh->GetVertices()[i];
                bufferMem[i].normal_ = mesh->GetNormals()[i];
                bufferMem[i].texCoords_ = glm::vec2(mesh->GetTexCoords(0)[i]);
            }
            gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo);
            gl::glBufferData(gl::GL_ARRAY_BUFFER, bufferMem.size() * sizeof(SimpleMeshVertex), bufferMem.data(), gl::GL_STATIC_DRAW);
            gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
            return vbo;
        }
    };


    struct AnimMeshVertex
    {
        glm::vec3 position_;
        glm::vec3 normal_;
        glm::vec2 texCoords_;
        glm::uvec4 boneIndices_;
        glm::vec4 boneWeights_;

        AnimMeshVertex() : position_(0.0f), normal_(0.0f), texCoords_(0.0f), boneIndices_(0), boneWeights_(0.0f) {}
        AnimMeshVertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::uvec4& indices, const glm::vec4& weights) : position_(pos), normal_(normal), texCoords_(tex), boneIndices_(indices), boneWeights_(weights) {}
        static void SetVertexAttributes(const GPUProgram* program)
        {
            auto attribLoc = program->GetAttributeLocations({ "position", "normal", "texCoords", "indices", "weights" });

            if (attribLoc[0] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[0]);
                gl::glVertexAttribPointer(attribLoc[0], 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(AnimMeshVertex), reinterpret_cast<GLvoid*>(offsetof(AnimMeshVertex, position_)));
            }
            if (attribLoc[1] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[1]);
                gl::glVertexAttribPointer(attribLoc[1], 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(AnimMeshVertex), reinterpret_cast<GLvoid*>(offsetof(AnimMeshVertex, normal_)));
            }
            if (attribLoc[2] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[2]);
                gl::glVertexAttribPointer(attribLoc[2], 2, gl::GL_FLOAT, gl::GL_FALSE, sizeof(AnimMeshVertex), reinterpret_cast<GLvoid*>(offsetof(AnimMeshVertex, texCoords_)));
            }
            if (attribLoc[3] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[3]);
                gl::glVertexAttribIPointer(attribLoc[3], 4, gl::GL_UNSIGNED_INT, sizeof(AnimMeshVertex), reinterpret_cast<GLvoid*>(offsetof(AnimMeshVertex, boneIndices_)));
            }
            if (attribLoc[4] != -1) {
                gl::glEnableVertexAttribArray(attribLoc[4]);
                gl::glVertexAttribPointer(attribLoc[4], 4, gl::GL_FLOAT, gl::GL_FALSE, sizeof(AnimMeshVertex), reinterpret_cast<GLvoid*>(offsetof(AnimMeshVertex, boneWeights_)));
            }
        }

        static GLuint CreateVertexBuffer(const Mesh* mesh)
        {
            GLuint vbo = 0;
            gl::glGenBuffers(1, &vbo);
            std::vector<AnimMeshVertex> bufferMem(mesh->GetVertices().size());
            for (auto i = 0U; i < mesh->GetVertices().size(); ++i) {
                bufferMem[i].position_ = mesh->GetVertices()[i];
                bufferMem[i].normal_ = mesh->GetNormals()[i];
                bufferMem[i].texCoords_ = glm::vec2(mesh->GetTexCoords(0)[i]);
                bufferMem[i].boneIndices_ = mesh->GetBoneIndices()[i];
                bufferMem[i].boneWeights_ = mesh->GetBoneWeights()[i];
            }
            gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo);
            gl::glBufferData(gl::GL_ARRAY_BUFFER, bufferMem.size() * sizeof(AnimMeshVertex), bufferMem.data(), gl::GL_STATIC_DRAW);
            gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
            return vbo;
        }
    };
}

#include <algorithm>
#include <iostream>
#include <frucht/spritebatch.hpp>

namespace Frucht {

SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
{

}

SpriteBatch::~SpriteBatch()
{

}
    
void SpriteBatch::init()
{
    createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
    m_sortType = sortType;
    m_renderBatches.clear();
    m_glyphs.clear();
}
    
void SpriteBatch::end()
{
    m_glyphsPointers.resize(m_glyphs.size());
    for (int i = 0; i < m_glyphs.size(); i++) {
        m_glyphsPointers[i] = &m_glyphs[i];
    }
    sortGlyphs();    
    createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
{
    m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::renderBatch()
{
//    std::cout << "renderbatch" << std::endl;
    glBindVertexArray(m_vao);

    for (int i = 0; i < m_renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
        glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
    }

    glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
    std::vector <Vertex> vertices;
    vertices.resize(m_glyphs.size() * 6);

    if (m_glyphs.empty()) {
        return;
    }
    
    int offset = 0;
    int cv = 0; // current vertex
    m_renderBatches.emplace_back(offset, 6, m_glyphsPointers[0]->texture);
    vertices[cv++] = m_glyphsPointers[0]->topLeft;
    vertices[cv++] = m_glyphsPointers[0]->bottomLeft;
    vertices[cv++] = m_glyphsPointers[0]->bottomRight;
    vertices[cv++] = m_glyphsPointers[0]->bottomRight;
    vertices[cv++] = m_glyphsPointers[0]->topRight;
    vertices[cv++] = m_glyphsPointers[0]->topLeft;
    offset += 6;

    for (int cg = 1; cg < m_glyphs.size(); cg++) {
        if (m_glyphsPointers[cg]->texture != m_glyphsPointers[cg - 1]->texture) {
            m_renderBatches.emplace_back(offset, 6, m_glyphsPointers[cg]->texture);
        } else {
            m_renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = m_glyphsPointers[cg]->topLeft;
        vertices[cv++] = m_glyphsPointers[cg]->bottomLeft;
        vertices[cv++] = m_glyphsPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphsPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphsPointers[cg]->topRight;
        vertices[cv++] = m_glyphsPointers[cg]->topLeft;      
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // orphan buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);   
    // upload data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
    if (m_vao == 0) {
        glGenVertexArrays(1, &m_vao);
    }
    glBindVertexArray(m_vao);

    if (m_vbo == 0) {
       glGenBuffers(1, &m_vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);    
   
    glEnableVertexAttribArray(0); // First element - only positions
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Pos pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // Attribarray, 2D (xy) 
    // Color pointer (second element (1), 4 variables)
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    
    glBindVertexArray(0);   
}

void SpriteBatch::sortGlyphs()
{
    switch (m_sortType) {
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareFrontToBack);
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareBackToFront);
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareTexture);
            break;
    }
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
    return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
    return (a->depth > b->depth);   
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
    return (a->texture < b->texture);
}

}

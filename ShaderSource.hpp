#ifndef SHADERSOURCE_HPP
#define SHADERSOURCE_HPP

#include <QColor>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <memory>
#include "Item.hpp"
#include "Node.hpp"

namespace SceneGraph {

class ShaderSource : public SceneGraph::Item {
 public:
  class ShaderNode : public Node, public QOpenGLFunctions {
   private:
    friend class ShaderSource;

    std::unique_ptr<QOpenGLFramebufferObject> m_fbo;
    TransformNode* m_capturedNode;
    QColor m_background;
    QSize m_size;
    QRectF m_viewport;
    uint m_lastUpdate;

    void update(ShaderSource* i);

   public:
    ShaderNode(QSize size, Node* = nullptr);
    ~ShaderNode();

    void updateTexture();
    inline QOpenGLFramebufferObject* texture() { return m_fbo.get(); }
  };

 private:
  SceneGraph::Item m_sourceItem;
  QRectF m_sourceRect;
  QSize m_textureSize;
  QColor m_background;
  ShaderNode* m_node;

 protected:
  std::unique_ptr<Node> synchronize(std::unique_ptr<Node> old);

 public:
  explicit ShaderSource(SceneGraph::Item* parent = nullptr);
  ~ShaderSource();

  inline SceneGraph::Item* sourceItem() { return &m_sourceItem; }

  inline QRectF sourceRect() const { return m_sourceRect; }
  void setSourceRect(QRectF);

  inline QSize textureSize() const { return m_textureSize; }
  void setTextureSize(QSize);

  inline QColor background() const { return m_background; }
  void setBackground(QColor);

  inline ShaderNode* shaderNode() const { return m_node; }

  void invalidate();
};
}

#endif  // SHADERSOURCE_HPP

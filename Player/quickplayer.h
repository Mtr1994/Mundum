#ifndef QUICKPLAYER_H
#define QUICKPLAYER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

class QuickPlayer : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit QuickPlayer(QWidget *parent = nullptr);
    ~QuickPlayer();

    // 测试使用，变化随机颜色
    void changeColor();

private:
    void init();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    // 着色器
    QOpenGLShaderProgram mShaderProgram;

    /// 指定圆角半径
    float mCornerRadius = 9;

    // 颜色位置
    int mColorLocation = -1;

    // 颜色变换参数
    float mColorRatio = 1.0;

    // 纹理对象
    unsigned int mTextureID = -1;

    // 纹理长度
    int mTextureWidth = 0;

    // 纹理高度
    int mTextureHeight = 0;

    // 纹理数据
    unsigned char *mTextureBuffer = nullptr;
};

#endif // QUICKPLAYER_H

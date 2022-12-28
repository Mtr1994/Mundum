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
};

#endif // QUICKPLAYER_H

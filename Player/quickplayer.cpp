#include "quickplayer.h"

// test
#include <QDebug>

QuickPlayer::QuickPlayer(QWidget *parent)
    : QOpenGLWidget{parent}
{
    init();
}

QuickPlayer::~QuickPlayer()
{
    mShaderProgram.release();
}

void QuickPlayer::init()
{
    // 抗锯齿
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(32);
    setFormat(surfaceFormat);
}

void QuickPlayer::initializeGL()
{
    // 不调用这句话，就不能使用 gl 开头的函数，程序会崩溃
    initializeOpenGLFunctions();

    // 着色器文件不能使用 UTF-8-BOM 编码，会报错，只能采用 UTF-8 编码

    // 加载顶点着色器
    bool status = mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Resource/shader/shader.vert");
    if (!status)
    {
        qDebug() << "parse vertex shader fail " << mShaderProgram.log();
        return;
    }

    // 加载片段着色器
    status= mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Resource/shader/shader.frag");
    if (!status)
    {
        qDebug() << "parse fragment shader fail " << mShaderProgram.log();
        return;
    }

    // 链接程序
    status = mShaderProgram.link();
    if (!status)
    {
        qDebug() << "link shader fail " << mShaderProgram.log();
        return;
    }

    float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

void QuickPlayer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void QuickPlayer::paintGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mShaderProgram.programId());

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

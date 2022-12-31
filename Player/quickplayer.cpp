#include "quickplayer.h"
#include "Sdk/stb_image/stb_image.h"

#include <QRandomGenerator>

// test
#include <QDebug>

// 博客 ： https://blog.csdn.net/weixin_44478077/article/details/124061067

QuickPlayer::QuickPlayer(QWidget *parent)
    : QOpenGLWidget{parent}
{
    init();
}

QuickPlayer::~QuickPlayer()
{
    mShaderProgram.release();
}

void QuickPlayer::changeColor()
{
    mColorRatio = QRandomGenerator::global()->bounded(0.5f) + 0.5;
    update();
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
    bool status = mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Resource/shader/shader_rgba.vert");
    if (!status)
    {
        qDebug() << "parse vertex shader fail " << mShaderProgram.log();
        return;
    }

    // 加载片段着色器
    status= mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Resource/shader/shader_rgba.frag");
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

    // 画 三角形
    {
//        float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

//        unsigned int buffer;
//        glGenBuffers(1, &buffer);
//        glBindBuffer(GL_ARRAY_BUFFER, buffer);
//        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

//        glUseProgram(mShaderProgram.programId());

//        mColorLocation = glGetUniformLocation(mShaderProgram.programId(), "u_Color");
//        if (mColorLocation < 0)
//        {
//            qDebug() << "can not find uniform u_Color";
//            return;
//        }
//        glUniform4f(mColorLocation, 0.2f, 0.5f, 0.8f, 1.0f);
    }

    // 画 纹理 （图片）
    {
        glUseProgram(mShaderProgram.programId());

        float vertices[]
        {
            // ---- 位置 ----       - 纹理坐标 -
             0.5f,  0.5f, 0.0f,    1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,    0.0f, 1.0f    // 左上
        };

        unsigned int indices[]
        {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // load and create a texture
        // -------------------------
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

        unsigned int ot = glGetUniformLocation(mShaderProgram.programId(), "ourTexture");
        if (ot < 0)
        {
            qDebug() << "can not find uniform ourTexture";
            return;
        }
        glUniform1i(ot, 0);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_set_flip_vertically_on_load(true);

        int channel = 0;
        mTextureBuffer = stbi_load(std::string("Demo9527.png").c_str(), &mTextureWidth, &mTextureHeight, &channel, 3);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mTextureWidth, mTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mTextureBuffer);

        if (mTextureBuffer) stbi_image_free(mTextureBuffer);
    }
}

void QuickPlayer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void QuickPlayer::paintGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //glUniform4f(mColorLocation, 0.2f, 0.4f, 0.6f * mColorRatio, 1.0f);

    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindTexture(GL_TEXTURE_2D, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

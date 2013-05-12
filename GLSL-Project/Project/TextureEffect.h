#ifndef TextureEffect_h
#define TextureEffect_h

#include "Effect.h"
#include <SOIL.h>

class TextureEffect: public Effect{
private:
    GLuint texture1, texture2;

	GLint LoadGLTexture(const char *filename) 
	{
		GLuint _texture;
		_texture = SOIL_load_OGL_texture
		(
		 filename,
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
		 );
    
		if(_texture == 0) {
			printf( "[ERROR] SOIL loading error: '%s'\n", SOIL_last_result() );
		}

		glBindTexture(GL_TEXTURE_2D, _texture); 
  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		return _texture;
	}
public:
    TextureEffect(int screenWidth, int screenHeight)
		:Effect("texture_effect.frag",&screenWidth, &screenHeight)
	{
		texture1 = glGetUniformLocation(programID, "texture1");
        if (texture1 == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "texture1");
        }

        texture2 = glGetUniformLocation(programID, "texture2");
        if (texture2 == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "texture2");
        }
    }
    virtual void draw()
	{
        glUseProgram(programID);

		glActiveTexture(GL_TEXTURE1);
		LoadGLTexture("balloon.jpg");
        glUniform1i(texture1, 1);

		glActiveTexture(GL_TEXTURE2);
		LoadGLTexture("ramp.png");
        glUniform1i(texture2, 2);

		glActiveTexture(GL_TEXTURE0);

        Effect::draw();
	}
};

#endif

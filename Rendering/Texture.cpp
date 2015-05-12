#include "Texture.h"

/**
*	@brief vyrobi OpenGL texturu z bitmapy
*	@param[in] p_bitmap je obrazek textury
*	@param[in] n_internal_format je pozadovany format ulozeni textury na graficke karte (format obrazku je v typu TBmp vzdy GL_RGBA)
*	@return vraci id textury (neuvazuje neuspech)
*/
GLuint n_GLTextureFromBitmap(const TBmp *p_bitmap, GLenum n_internal_format = GL_RGBA8)
{
	GLuint n_tex;
	glGenTextures(1, &n_tex);
	glBindTexture(GL_TEXTURE_2D, n_tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, n_internal_format, p_bitmap->n_width, p_bitmap->n_height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, p_bitmap->p_buffer);
	// specifikujeme data textury

	glGenerateMipmap(GL_TEXTURE_2D);
	// nechame OpenGL spocitat jeji mipmapy

	return n_tex;
}

/**
*	@brief vraci texturu nactenou ze souboru ve formatu png
*	@param[in] imagepath jmeno souboru
*/
GLuint LoadTextureFromPNGFile(const char * imagepath){

	TBmp * bitmap;
	if (!(bitmap = CPngCodec::p_Load_PNG(imagepath))){
		std::cerr << "error: failed to load \'.png file\'" << std::endl;
		system("PAUSE");
		return false;
	}

	GLuint texture = n_GLTextureFromBitmap(bitmap, GL_RGBA8);
	bitmap->Delete();

	return texture;
}
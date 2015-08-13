#include "loadText.h"
#include <cstdio>
#include <cstring>
#include <iostream>

namespace byhj
{

	const char * loadText(const char *fn)
	{
		FILE *fp;
		char *content = NULL;
		int count = 0;

		if (fn != NULL) {

			fopen_s(&fp, fn, "rt");
			if (!fp){

#ifdef WINDOW_PLATFORM
				MessageBox(NULL, "Can not open the shader file", "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
				std::cerr << "Can not open the shader file:" << fn << std::endl;

#endif
				return NULL;
			}
			if (fp != NULL) {
				fseek(fp, 0, SEEK_END);
				count = ftell(fp);
				rewind(fp);

				if (count > 0) {
					content = (char *)malloc(sizeof(char)* (count + 1));
					count = fread(content, sizeof(char), count, fp);
					content[count] = '\0';
				}
				fclose(fp);
			}
			else
				std::cout << "Fail to open the shader file" << std::endl;
		}
		return content;
	}

}
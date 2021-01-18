#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>

class Window {
	public:
		Window();
		virtual ~Window();

	private:
		void initWindow();
		int createWindow();
		GLFWwindow* window;
		const unsigned int WIDTH = 800;
		const unsigned int HEIGHT= 600;
		void update();
		void processInput(GLFWwindow* window);
};

#endif /* WINDOW_H_ */

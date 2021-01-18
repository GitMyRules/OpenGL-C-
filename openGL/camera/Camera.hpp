

#ifndef CAMERA_H
#define CAMERA_H

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader/Shader.hpp"
#include <iostream>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  6.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		bool firstMouse = true;
		float lastX, lastY;

		// Constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = glm::vec3(posX, posY, posZ);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(Position, Position + Front, Up);
		}

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction, float deltaTime)
		{
			float velocity = MovementSpeed * deltaTime;
			if (direction == FORWARD)
				Position += Front * velocity;
			if (direction == BACKWARD)
				Position -= Front * velocity;
			if (direction == LEFT)
				Position -= Right * velocity;
			if (direction == RIGHT)
				Position += Right * velocity;
			Position.y += 0.0f;
		}

		void processkeyboard(GLFWwindow* window){
			if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				ProcessKeyboard(FORWARD, deltaTime);
			if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				ProcessKeyboard(BACKWARD, deltaTime);
			if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				ProcessKeyboard(LEFT, deltaTime);
			if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				ProcessKeyboard(RIGHT, deltaTime);
		}

		void mouseCallBack(GLFWwindow* window, double xpos, double ypos){
			if(firstMouse){
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}
			float xOffset = xpos - lastX;
			float yOffset = lastY - ypos; //reverse coordinate

			lastX = xpos;
			lastY = ypos;
			ProcessMouseMovement(xOffset, yOffset);
		}

		void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset){
			ProcessMouseScroll(yOffset);
		}

		void mousePosition(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT){
			lastX = WINDOW_WIDTH/2.0f;
			lastY = WINDOW_HEIGHT/2.0f;
		}

		void calcDeltaTime(){
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
		}

		void setCamera(Shader earthTexture, Shader sunTexture){
			glm::mat4 view = glm::mat4(1.0f);
			view = GetViewMatrix();

			earthTexture.use();
			earthTexture.setMat4("view", view);
			earthTexture.setVec3("viewPos", Position);

			sunTexture.use();
			sunTexture.setMat4("view", view);
		}

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
		{
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw   += xoffset;
			Pitch += yoffset;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch)
			{
				if (Pitch > 89.0f)
					Pitch = 89.0f;
				if (Pitch < -89.0f)
					Pitch = -89.0f;
			}

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset)
		{
			if (Zoom >= 1.0f && Zoom <= 45.0f)
				Zoom -= yoffset;
			if (Zoom <= 1.0f)
				Zoom = 1.0f;
			if (Zoom >= 45.0f)
				Zoom = 45.0f;
		}

	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors()
		{
			// Calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			// Also re-calculate the Right and Up vector
			Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			Up    = glm::normalize(glm::cross(Right, Front));
		}
};
#endif


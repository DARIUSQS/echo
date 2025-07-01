#include "Camera.h"
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Echo
{
    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        :m_Position(0.0f), m_Rotation(0.0f)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewMatrix = glm::mat4(1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), {0.0f, 0.0f, 1.0f});

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
        : m_Position(0.0f), m_CameraFront(0.0f), m_CameraUp({0.0f, 1.0f, 0.0f})
    {
        m_Rotation = {0.0f, 0.0f, 0.0f};
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
        m_ViewMatrix = glm::mat4(1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::SetRotation(float posX, float posY, float sensitivity) 
    {
        m_Rotation.pitch += (lastY - posY) * sensitivity;
        m_Rotation.yaw += (posX - lastX) * sensitivity;

        if(m_Rotation.pitch > 89.0f) m_Rotation.pitch = 89.0f;
        if(m_Rotation.pitch < -89.0f) m_Rotation.pitch = -89.0f;

        lastX = posX;
        lastY = posY;
        
        CalculateRotation();
    }

    void PerspectiveCamera::CalculateRotation() 
    {
        glm::vec3 dir;
        dir.x = glm::cos(glm::radians(m_Rotation.pitch)) * glm::cos(glm::radians(m_Rotation.yaw));
        dir.y = glm::sin(glm::radians(m_Rotation.pitch));
        dir.z = glm::sin(glm::radians(m_Rotation.yaw)) * glm::cos(glm::radians(m_Rotation.pitch));
        m_CameraFront = glm::normalize(dir);
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), -m_Position);
        transform = glm::lookAt(m_Position, m_Position + m_CameraFront , m_CameraUp);

        m_ViewMatrix = transform;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::RecalculateProjectionMatrix(float fov, float aspectRatio, float near, float far)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
        RecalculateViewMatrix();
    }
}

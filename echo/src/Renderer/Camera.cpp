#include "Camera.h"
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Echo
{
    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        :m_Position(0.0f), m_Rotation(0)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewMatrix = glm::mat4(1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        glm::quat quater;
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}

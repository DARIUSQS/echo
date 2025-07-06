#include "CameraController.h"
#include "InputTemplate.h"

namespace Echo 
{
    void PerspectiveCameraController::OnUpdate()
    {
        m_Camera.SetPosition(m_CameraPos);
        m_Camera.SetRotation(Echo::Input::GetMouseX(), Echo::Input::GetMouseY(), m_Sensitivity);

        m_CameraDir = glm::vec3(0.0f);
        if(Echo::Input::IsKeyPressed(EC_KEY_W)) m_CameraDir += m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_D)) m_CameraDir += glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());
        if(Echo::Input::IsKeyPressed(EC_KEY_S)) m_CameraDir -= m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_A)) m_CameraDir -= glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());;
        if(Echo::Input::IsKeyPressed(EC_KEY_E)) m_CameraDir += m_Camera.GetCameraUp();
        if(Echo::Input::IsKeyPressed(EC_KEY_Q)) m_CameraDir -= m_Camera.GetCameraUp();
        if(Echo::Input::IsKeyPressed(EC_KEY_LEFT_SHIFT)) m_RunningMult = 2.0f;
        else m_RunningMult = 1.0f;

        if(glm::length(m_CameraDir)) m_CameraDir = glm::normalize(m_CameraDir);

        m_CameraPos += m_CameraDir * m_CameraSpeed * m_RunningMult * DeltaTime::Seconds();
    }

    void PerspectiveCameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&PerspectiveCameraController::OnWindowResize, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&PerspectiveCameraController::OnMouseScroll, this, std::placeholders::_1));
    }

    bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& event)
    {
        m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        m_Camera.RecalculateProjectionMatrix(m_Fov, m_AspectRatio, m_NearPlane, m_FarPlane);
        return 0;
    }
    
    bool PerspectiveCameraController::OnMouseScroll(MouseScrollEvent& event)
    {
        m_Fov -= event.GetYOffset();
        if(m_Fov < m_MinZoom) m_Fov = m_MinZoom;
        if(m_Fov > m_MaxZoom) m_Fov = m_MaxZoom;

        m_Camera.RecalculateProjectionMatrix(m_Fov, m_AspectRatio, m_NearPlane, m_FarPlane);
        return 0;
    }
}

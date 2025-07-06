#pragma once
#include "Camera.h"
#include "ecpch.h"

namespace Echo
{
    /// TODO 
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio)
            : m_Camera(-aspectRatio, aspectRatio, 1, -1) {}

        void OnUpdate();
        void OnEvent(Event& event);
        
    private:
        OrthographicCamera m_Camera;
    };

    class PerspectiveCameraController 
    {
    public:
            PerspectiveCameraController(float aspectRatio, float fov, float near, float far)
                : m_Camera(fov, aspectRatio, near, far), m_AspectRatio(aspectRatio), m_Fov(fov), m_NearPlane(near), m_FarPlane(far)
            {
                m_CameraPos = glm::vec3(0.0f);
            }

            void OnUpdate();
            void OnEvent(Event& event);

            const PerspectiveCamera& GetCamera() {return m_Camera;};

            void SetZoom(float min, float max) {m_MaxZoom = max, m_MinZoom = min;}
            void SetSensitivity(float sens) {m_Sensitivity = sens;}

            inline float GetSensitivity() const {return m_Sensitivity;}
            inline float GetZoom() const { return m_Fov;}
            inline float GetFov() const { return m_Fov;}
    private:
        bool OnWindowResize(WindowResizeEvent& event);
        bool OnMouseScroll(MouseScrollEvent& event);

        float m_AspectRatio, m_Fov, m_NearPlane, m_FarPlane;
        float m_MinZoom = 15.0f, m_MaxZoom = 75.0f, m_Sensitivity = 0.1f;
        PerspectiveCamera m_Camera;

        glm::vec3 m_CameraDir, m_CameraPos;
        float m_CameraSpeed = 1.0f, m_RunningMult = 1.0f;
    };
}

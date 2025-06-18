#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Echo 
{
    class Camera 
    {
        public:
            virtual const glm::vec3& GetPosition() const = 0;
            virtual void SetPosition(const glm::vec3& position) = 0;

            virtual const glm::mat4& GetViewMatrix() const = 0;
            virtual const glm::mat4& GetProjectionMatrix() const = 0;
            virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
        protected:
            virtual void RecalculateViewMatrix() = 0;
    };

    class OrthographicCamera : public Camera
    {
        public:
            OrthographicCamera(float left, float right, float top, float bottom);
 
            virtual const glm::vec3& GetPosition() const override {return m_Position;}
            virtual void SetPosition(const glm::vec3& position) override {m_Position = position; RecalculateViewMatrix();}

            float GetRotation() const {return m_Rotation;}
            void SetRotation(float rotation) {m_Rotation = rotation;}

            virtual const glm::mat4& GetViewMatrix() const override {return m_ViewMatrix;}
            virtual const glm::mat4& GetProjectionMatrix() const override {return m_ProjectionMatrix;}
            virtual const glm::mat4& GetViewProjectionMatrix() const override {return m_ViewProjectionMatrix;}
        protected:
            virtual void RecalculateViewMatrix() override;
        private:
            glm::mat4 m_ViewMatrix;
            glm::mat4 m_ProjectionMatrix;
            glm::mat4 m_ViewProjectionMatrix;

            glm::vec3 m_Position;
            float m_Rotation;
    };

    struct CameraRotation 
    {
        double pitch, yaw, roll;  
    };
    

    inline std::string format_as(const CameraRotation& c)
    {
        std::stringstream ss;
        ss << "{Yaw: " << c.yaw << "; Pitch: " << c.pitch << "; Roll: " << c.roll << "}";
        return ss.str();
    }

    class PerspectiveCamera : public Camera
    {
        public:
            PerspectiveCamera(float fov, float aspectRatio, float near, float far);

            virtual const glm::vec3& GetPosition() const override {return m_Position;}
            virtual void SetPosition(const glm::vec3& position) override {m_Position = position; RecalculateViewMatrix();}
 
            void CalculateRotation();
            void SetRotation(float PosX, float PosY, float sensitivity);
            const CameraRotation& GetRotation() const {return m_Rotation;}

            virtual const glm::mat4& GetViewMatrix() const override {return m_ViewMatrix;}
            virtual const glm::mat4& GetProjectionMatrix() const override {return m_ProjectionMatrix;}
            virtual const glm::mat4& GetViewProjectionMatrix() const override {return m_ViewProjectionMatrix;}

            const glm::vec3& GetCameraFront() const {return m_CameraFront;}
            const glm::vec3& GetCameraUp() const {return m_CameraUp;}
        protected:
            virtual void RecalculateViewMatrix() override;
        private:         

            glm::vec3 pos;

            glm::mat4 m_ViewMatrix;
            glm::mat4 m_ProjectionMatrix;
            glm::mat4 m_ViewProjectionMatrix;

            glm::vec3 m_Position, m_CameraFront, m_CameraUp;
            
            int lastX, lastY;

            CameraRotation m_Rotation;
    };
}

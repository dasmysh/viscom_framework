/**
 * @file   ApplicationNodeImplementation.h
 * @author Sebastian Maisch <sebastian.maisch@uni-ulm.de>
 * @date   2016.11.30
 *
 * @brief  Declaration of the application node implementation common for coordinator and worker nodes.
 */

#pragma once

#include "core/app/ApplicationNodeBase.h"

namespace viscom {

    class MeshRenderable;
    class AnimMeshRenderable;
    class AnimationState;

    struct demoSyncedInfo {
        glm::vec3 circleData_;
        glm::vec2 displayPos0_;
    };

    class ApplicationNodeImplementation : public ApplicationNodeBase
    {
    public:
        explicit ApplicationNodeImplementation(ApplicationNodeInternal* appNode);
        ApplicationNodeImplementation(const ApplicationNodeImplementation&) = delete;
        ApplicationNodeImplementation(ApplicationNodeImplementation&&) = delete;
        ApplicationNodeImplementation& operator=(const ApplicationNodeImplementation&) = delete;
        ApplicationNodeImplementation& operator=(ApplicationNodeImplementation&&) = delete;
        virtual ~ApplicationNodeImplementation() override;

        virtual void UpdateFrame(double currentTime, double elapsedTime) override;
        virtual void ClearBuffer(FrameBuffer& fbo) override;
        virtual void DrawFrame(FrameBuffer& fbo) override;

#ifdef VISCOM_USE_SGCT
        virtual void PreSync() override;
        virtual void UpdateSyncedInfo() override;
        void EncodeData() override;
        void DecodeData() override;
#endif

        virtual bool KeyboardCallback(int key, int scancode, int action, int mods) override;
        virtual bool MousePosCallback(double x, double y) override;


    private:
        /** Holds the shader program for drawing the background. */
        std::shared_ptr<GPUProgram> backgroundProgram_;
        /** Holds the location of the MVP matrix. */
        GLint backgroundMVPLoc_ = -1;

        /** Holds the shader program for drawing the foreground triangle. */
        std::shared_ptr<GPUProgram> triangleProgram_;
        /** Holds the location of the MVP matrix. */
        GLint triangleMVPLoc_ = -1;

        /** Holds the shader program for drawing the Mousepoint. */
        std::shared_ptr<GPUProgram> mousepointProgram_;
        /** Holds the location of the MVP matrix. */
        GLint mousepointMVPLoc_ = -1;

        /** Holds the shader program for drawing the demoCircles. */
        std::shared_ptr<GPUProgram> demoCirclesProgram_;
        /** Holds the location of the MVP matrix. */
        GLint demoCirclesMVPLoc_ = -1;

        GLint demoCirclesHitLoc_ = -1;
        GLint demoCirclesSizeLoc_ = -1;
        GLint demoCirclesRatioLoc_ = -1;

        GLint demoCirclesCenterPos_ = -1;

        /** Holds the shader program for drawing the foreground teapot. */
        std::shared_ptr<GPUProgram> teapotProgram_;
        /** Holds the location of the VP matrix. */
        GLint teapotVPLoc_ = -1;

        /** Holds the shader program for drawing the animated foreground robot. */
        std::shared_ptr<GPUProgram> robotProgram_;
        /** Holds the location of the VP matrix. */
        GLint robotVPLoc_ = -1;

        /** Holds the number of vertices of the background grid. */
        unsigned int numBackgroundVertices_ = 0;
        /** Holds the vertex buffer for the background grid. */
        GLuint vboBackgroundGrid_ = 0;
        /** Holds the vertex array object for the background grid. */
        GLuint vaoBackgroundGrid_ = 0;

        /** Holds the number of vertices of the circles demo. */
        unsigned int numCirclesVertices_ = 0;
        /** Holds the vertex buffer for the background grid. */
        GLuint vboCircles_ = 0;
        /** Holds the vertex array object for the background grid. */
        GLuint vaoCircles_ = 0;
        GLint demoCirclesWindowSize_ = -1;

        /** Holds the teapot mesh. */
        std::shared_ptr<Mesh> teapotMesh_;
        /** Holds the teapot mesh renderable. */
        std::unique_ptr<MeshRenderable> teapotRenderable_;

        /** Holds the robot mesh. */
        std::shared_ptr<Mesh> robotMesh_;
        /** Holds the robot mesh renderable. */
        std::unique_ptr<AnimMeshRenderable> robotRenderable_;
        /** Holds the robot meshes animation state. */
        std::unique_ptr<AnimationState> robotAnimationState_;

        glm::mat4 triangleModelMatrix_ = glm::mat4{ 1.0f };
        glm::mat4 teapotModelMatrix_ = glm::mat4{ 1.0f };
        glm::mat4 robotModelMatrix_ = glm::mat4{ 1.0f };
        glm::vec3 camPos_ = glm::vec3{ 0.0f };
        glm::vec3 camRot_ = glm::vec3{ 0.0f };

        double posx, posy, posdx, posdy;
        glm::mat4 demoCirclesModelMatrix_;

    protected:
#ifdef VISCOM_USE_SGCT
        /** Holds the synchronized object (local). */
        demoSyncedInfo demoSyncInfoLocal_;
        /** Holds the synchronized object (synced). */
        sgct::SharedObject<demoSyncedInfo> demoSyncInfoSynced_;
#endif
        /** Holds the mousePoint Model Matrix */
        glm::mat4 mousepointModelMatrix_;
        bool demoCirclesMoved = false;
        int hitCircle = 0;
        float circleMoveStartTime = 0.0f;
        float circler_ = 0.05f;
        float circlex_ = 0.0f;
        float circley_ = 0.0f;
        int demoPoints = 0;
        std::vector<ovr::DeviceInfo> connectedDevices_;
        glm::vec2 displayPos;
    };
}

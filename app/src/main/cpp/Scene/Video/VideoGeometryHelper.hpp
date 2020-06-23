//
// Created by geier on 23/06/2020.
//

#ifndef FPV_VR_OS_VIDEOGEOMETRYHELPER_HPP
#define FPV_VR_OS_VIDEOGEOMETRYHELPER_HPP

#include <TexturedGeometry.hpp>
#include <SphereBuilder.hpp>

class VideoGeometryHelper{
public:
    //Normal: Render a rectangle
    //Stereo: One decoded frame contains images for left and right eye
    //Render left frame into a rectangle with u->{0,0,5} and right frame int a rectangle with u->{0.5,1.0}
    //Degree360: 360 degree video, rendered onto a sphere instead of a quad
    enum VIDEO_RENDERING_MODE{
        RM_2D_MONOSCOPIC,RM_2D_STEREO,
        //2 different modes - mapping in shader or before uploading
        RM_360_DUAL_FISHEYE_INSTA360_1,
        RM_360_DUAL_FISHEYE_INSTA360_2,
        //Rest of the stuff added by webbn
        RM_360_KODAK_SP360_4K_DUAL,RM_360_KODAK_SP360_4K_SINGLE,RM_360_FIREFLY_SPLIT_4K,RM_360_1080P_USB,RM_360_STEREO_PI};

    static const unsigned int TESSELATION_FACTOR=10;
    static TexturedGeometry::Mesh createMeshForMode(const VIDEO_RENDERING_MODE videoRenderingMode,const float positionZ, const float width, const float height){
        switch (videoRenderingMode){
            case RM_2D_MONOSCOPIC:
                return TexturedGeometry::Mesh(TexturedGeometry::makeTesselatedVideoCanvas(TESSELATION_FACTOR,{0,0,positionZ},{width,height},0.0f,1.0f),GL_TRIANGLES);
                break;
            case RM_2D_STEREO:
                return TexturedGeometry::Mesh(TexturedGeometry::makeTesselatedVideoCanvas(TESSELATION_FACTOR,{0,0,positionZ},{width,height},0.0f,0.5f),GL_TRIANGLES);
                break;
            case RM_360_DUAL_FISHEYE_INSTA360_1:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereEquirectangularMonoscopic(),GL_TRIANGLE_STRIP);
                break;
            case RM_360_DUAL_FISHEYE_INSTA360_2:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereDualFisheyeInsta360(),GL_TRIANGLE_STRIP);
                break;
            case RM_360_KODAK_SP360_4K_DUAL:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereFisheye(UvSphere::ROTATE_0,0.5,0.65,190,0.05,0),GL_TRIANGLE_STRIP);
                break;
            case RM_360_KODAK_SP360_4K_SINGLE:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereFisheye(UvSphere::ROTATE_180,0.5,0.5,190,0.0,0),GL_TRIANGLE_STRIP);
                break;
            case RM_360_FIREFLY_SPLIT_4K:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereFisheye(UvSphere::ROTATE_180,0.5,0.5,210,0.05,0),GL_TRIANGLE_STRIP);
                break;
            case RM_360_1080P_USB:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereFisheye(UvSphere::ROTATE_270,0.5,0.5,210,0.05,0),GL_TRIANGLE_STRIP);
                break;
            case RM_360_STEREO_PI:
                return TexturedGeometry::Mesh(SphereBuilder::createSphereFisheye(UvSphere::ROTATE_270,0.5,0.5,210,0.05,0),GL_TRIANGLE_STRIP);
                break;
            default:
                assert("Unknown type ");
        }
    }

};
#endif //FPV_VR_OS_VIDEOGEOMETRYHELPER_HPP

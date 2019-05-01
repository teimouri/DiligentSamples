/*     Copyright 2015-2019 Egor Yusov
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#pragma once 

#include "SampleBase.h"
#include "GLTFLoader.h"
#include "GLTF_PBR_Renderer.h"
#include "BasicMath.h"

namespace Diligent
{

class GLTFViewer final : public SampleBase
{
public:
    ~GLTFViewer();
    virtual void Initialize(IEngineFactory*   pEngineFactory,
                            IRenderDevice*    pDevice, 
                            IDeviceContext**  ppContexts, 
                            Uint32            NumDeferredCtx, 
                            ISwapChain*       pSwapChain)override final;
    virtual void Render()override final;
    virtual void Update(double CurrTime, double ElapsedTime)override final;
    virtual const Char* GetSampleName()const override final{return "GLTF Viewer";}

private:
    void CreateEnvMapPSO();
    void CreateEnvMapSRB();

    enum class BackgroundMode
    {
        None,
        EnvironmentMap,
        Irradiance,
        PrefilteredEnvMap
    }m_BackgroundMode = BackgroundMode::PrefilteredEnvMap;

    GLTF_PBR_Renderer::RenderInfo m_RenderParams;

    Quaternion m_Rotation;
    float3     m_LightDirection;
    float4     m_LightColor      = float4(1,1,1,1);
    float      m_LightIntensity  = 10;
    float      m_EnvMapMipLevel  = 1.f;

    std::unique_ptr<GLTF_PBR_Renderer> m_GLTFRenderer;
    std::unique_ptr<GLTF::Model>       m_Model;
    RefCntAutoPtr<IBuffer> m_CameraAttribsCB;
    RefCntAutoPtr<IBuffer> m_LightAttribsCB;
    RefCntAutoPtr<IPipelineState>         m_EnvMapPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_EnvMapSRB;
    RefCntAutoPtr<ITextureView>           m_EnvironmentMapSRV;
    RefCntAutoPtr<IBuffer>                m_EnvMapRenderAttribsCB;
};

}
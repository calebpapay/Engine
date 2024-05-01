#pragma pack_matrix( row_major )

// ------------------------------------------
// tx - t is texture buuffer, x - slot
// ------------------------------------------
Texture2D mainTexture : register(t0);

// ------------------------------------------
// sx - s is sampler, x - slot
// ------------------------------------------
SamplerState aSampler : register(s0);

cbuffer AA3 : register(b5) // slot 5 (ConstantBufferSlot::UV_Correction)
{
    float4x4 uvMatrix;
}

cbuffer AA4 : register(b6) // slot 6 (ConstantBufferSlot::SpriteColor)
{
    float4 InColorX;
}


// -------------------------------------
//  Pixel Shader Input Sematics
//        TEXCOORD - uv tex coord
//      Note: output layout needs to be the same for input input pixel
// -------------------------------------
struct PixelShaderInput
{
    float2 tex : TEXCOORD;
    float4 position : SV_POSITION;
    //matrix uvMat : MONKEY;
};




// --------------------------------------------------------
//  Pixel Shader Main()
//      SV_TARGET - System Value Target
//                  output stored in a render target 0  (only one target)
// --------------------------------------------------------
float4 Sprite_Main(PixelShaderInput inData) : SV_TARGET
{
   	// correct the UV coordinates, originally its (0,0 - 1,1)
	// scale and translate to the correct sub image on the texture

    float4 uv_vec;
    uv_vec.xy = inData.tex.xy;
    uv_vec.z = 0.0f;
    uv_vec.w = 1.0f;

    float4 uv_corrected = mul(uv_vec, uvMatrix);



    return InColorX * mainTexture.Sample(aSampler, uv_corrected.xy);
    
    //return mainTexture.Sample(aSampler, inData.tex);
}

// --- End of File ---

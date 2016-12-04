#include "WaterRenderer.h"
#include "../Light.h"
#include "../MasterRenderer.h"

WaterRenderer::WaterRenderer(Camera* camera) {
	this->camera = camera;
	MasterRenderer::Register(this);
}

WaterRenderer::~WaterRenderer() {
	waters.clear();
	MasterRenderer::Unregister(this);
}

void WaterRenderer::Register(Water* water) {
	Shader* shader = water->GetShader();

	shader->Bind();
	shader->SetUniform1i("reflectionSampler", 0);
	shader->SetUniform1i("refractionSampler", 1);
	shader->SetUniform1i("dudvSampler", 2);
	shader->SetUniform1i("normalSampler", 3);
	shader->SetUniform1i("depthSampler", 4);
	shader->Unbind();

	waters.insert(water);
}

void WaterRenderer::Unregister(Water* water) {
	waters.erase(water);
}

void WaterRenderer::Render(WaterFrameBuffer* waterFrameBuffer) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (Water* water : waters) {
		Shader* shader = water->GetShader();
		VertexArray* vArray = water->GetMesh()->GetVertexArray();
		IndexBuffer* iBuffer = water->GetMesh()->GetIndexBuffer();

		shader->Bind();
		vArray->Bind();
		iBuffer->Bind();

		waterFrameBuffer->GetReflectionTexture()->Bind(0);
		waterFrameBuffer->GetRefractionTexture()->Bind(1);
		water->GetDUDV()->Bind(2);
		water->GetNormal()->Bind(3);
		glActiveTexture(GL_TEXTURE0 + 4);
		glBindTexture(GL_TEXTURE_2D, waterFrameBuffer->GetRefractionDepthTexture());

		shader->SetUniform1f("near", camera->GetNearClip());
		shader->SetUniform1f("far", camera->GetFarClip());
		shader->SetUniform3f("lightPosition", Light::position);
		shader->SetUniform3f("lightColor", Light::color);
		shader->SetUniform3f("cameraPosition", camera->GetPosition());
		shader->SetUniform1f("moveFactor", water->GetMoveFactor());
		shader->SetUniform1f("textureTiling", water->textureTiling);
		shader->SetUniform1f("distorsionStrength", water->distorsionStrength);
		shader->SetUniformMatrix4fv("gProj", camera->GetProjectionMatrix());
		shader->SetUniformMatrix4fv("gCamera", camera->GetViewMatrix());
		shader->SetUniformMatrix4fv("gWorld", water->GetTransform()->GetMatrix());

		glDrawElements(GL_TRIANGLES, iBuffer->GetCount(), GL_UNSIGNED_INT, 0);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		water->GetNormal()->Unbind();
		water->GetDUDV()->Unbind();
		waterFrameBuffer->GetRefractionTexture()->Unbind();
		waterFrameBuffer->GetReflectionTexture()->Unbind();

		iBuffer->Unbind();
		vArray->Unbind();
		shader->Unbind();
	}

	glDisable(GL_BLEND);
}
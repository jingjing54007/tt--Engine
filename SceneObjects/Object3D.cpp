// Copyright � 2013 Tom Tondeur
// 
// This file is part of tt::Engine.
// 
// tt::Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// tt::Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with tt::Engine.  If not, see <http://www.gnu.org/licenses/>.

#include "Object3D.h"

#include "../Services/ServiceLocator.h"
#include "../Graphics/Materials/Object3DMaterial.h"
#include "../Graphics/Materials/SkinnedMaterial.h"

Object3D::Object3D(void)
{
	auto pTransform = new TransformComponent();
	auto pModel = new ModelComponent(_T("Resources/box3bones.bin"),pTransform);
	
	SetComponent<TransformComponent>(pTransform);
	SetComponent<ModelComponent>(pModel);
}

Object3D::~Object3D(void)
{
	
}

//Methods

void Object3D::Initialize(void)
{
	auto pMat = MyServiceLocator::GetInstance()->GetService<ResourceService>()->Load<SkinnedMaterial>( _T("BasicMaterial") );
	GetComponent<ModelComponent>()->SetMaterial(pMat);
	pMat->SetDiffuse(_T("Resources/Vampire_Diffuse.dds"));
}

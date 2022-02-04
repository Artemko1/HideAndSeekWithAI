// Fill out your copyright notice in the Description page of Project Settings.


#include "DGHUD.h"
#include "Engine/Canvas.h"

void ADGHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
}

void ADGHUD::DrawCrossHair()
{
	const FVector2D Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	constexpr float LineSize = 6.0f;
	constexpr float Offset = 6.0f;
	constexpr float LineThickness = 1.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.X - Offset, Center.Y, Center.X - Offset - LineSize, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X + Offset, Center.Y, Center.X + Offset + LineSize, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y - Offset, Center.X, Center.Y - Offset - LineSize, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y + Offset, Center.X, Center.Y + Offset + LineSize, LineColor, LineThickness);
}

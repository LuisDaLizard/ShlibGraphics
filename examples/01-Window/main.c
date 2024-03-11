#include <Shlib.h>
#include <stdio.h>

void Update(float delta);

int main()
{
    Application *pApp = NULL;

    AppCreateInfo createInfo;
    createInfo.width = 800;
    createInfo.height = 600;
    createInfo.pTitle = "01 - Window";
    createInfo.pUpdateFunction = Update;

    ApplicationInit(&createInfo, &pApp);

    ApplicationRun(pApp);

    ApplicationFree(pApp);

    return 0;
}

void Update(float delta)
{
    printf("%.10f\n", delta);
}
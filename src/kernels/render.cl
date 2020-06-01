R"(

__kernel void Render(int tileSize, int width, int height, __global float* output)
{
	int tw = (width+(tileSize-1))/tileSize;
	int th = (height+(tileSize-1))/tileSize;
	int id = get_global_id(0);
	int tx = id%tw;
	int ty = id/th;

    if (ty > th)
	{
		return;
	}

	int xRange = min(width - (tx*tileSize), tileSize);
	int yRange = min(height- (ty*tileSize), tileSize);

    for (int x=0; x<xRange; x++)
	{
		for (int y=0; y<yRange; y++)
		{
			int index = (((tileSize * tx) + x) + (((tileSize * ty) + y)*width)) * 3;
			output[index] = x/((float)tileSize);
			output[index + 1] = y/((float)tileSize);
			output[index + 2] = (float)id/(tw*th);
		}
	}
}

)"
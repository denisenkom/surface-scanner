// критерий Пирсона о нормальном распределении

float sqrf(float x)
{
	return x*x;
}

float Xkr(float alpha, int m)
{
	float res;

	if (m == 4 && alpha == .05f)
	{
		return 9.5f;
	}
	else if (m <= 30)
	{
		//printf("Введите значение квантиля X2a(m) при a=%.2f,m=%i из таблицы 1.1.2.7:>", alpha, m);
		//scanf("%f", &res);
    log ("Введите значение квантиля X2a(m) при a=%.2f,m=%i из таблицы 1.1.2.7:>", alpha, m);
	}
	else
	{
		float z2a;
		//printf("Введите значение z2a для Ф(z2a)=%.7f:>",.5-alpha);
		//scanf("%f",&z2a);
    log("Введите значение z2a для Ф(z2a)=%.7f:>",.5-alpha);
		res = .5f*sqrf(sqrt(2*m-1)+z2a);
	}
	return res;
}


bool PirsonTest(float data[], int n, float alpha)
{
	float avg = 0;

	if (n < 100)
		log("Warning: PirsonTest(): To small data must be >100\n");
	
	{for (int i = 0; i < n; i++)
	{
		avg += data[i];
	}}
	avg /= n;

	float* ost = new float[n];
	float max = -100000;
	float min = 100000;
	{for (int i = 0; i < n; i++)
	{
		ost[i] = data[i] - avg;
		if (ost[i] > max)
			max = data[i];
		if (ost[i] < min)
			min = data[i];
	}}

	int freq[5] = {0};
	float delta = (max - min)/5;

	{for (int i = 0; i < n; i++)
	{
		if (ost[i] >= min && ost[i] < min + delta)
			freq[0]++;
		else if (ost[i] < min + 2*delta)
			freq[1]++;
		else if (ost[i] >= min + 2*delta && ost[i] < min + 3*delta)
			freq[2]++;
		else if (ost[i] >= min + 3*delta && ost[i] < min + 4*delta)
			freq[3]++;
		else if (ost[i] >= min + 4*delta)
			freq[4]++;
	}}
	float sum = 0;
	{for (int i = 0; i < 5; i++)
		sum += sqrf(freq[i]-.2f*n)/.2f/n;}

	return (sum < Xkr(alpha, 4));
}
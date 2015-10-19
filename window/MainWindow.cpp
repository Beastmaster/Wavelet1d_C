#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <math.h>

const double test_data[] = 
{
	2231
	,2172
	,2082
	,1987
	,1924
	,1928
	,2000
	,2104
	,2190
	,2241
	,2234
	,2175
	,2086
	,1992
	,1927
	,1930
	,2001
	,2104
	,2191
	,2243
	,2236
	,2177
	,2089
	,1995
	,1928
	,1929
	,1998
	,2103
	,2189
	,2241
	,2236
	,2179
	,2091
	,1996
	,1928
	,1928
	,1997
	,2101
	,2189
	,2241
	,2238
	,2181
	,2094
	,1998
	,1930
	,1928
	,1996
	,2100
	,2188
	,2243
	,2240
	,2183
	,2096
	,2001
	,1933
	,1929
	,1995
	,2098
	,2187
	,2242
	,2240
	,2184
	,2096
	,2002
	,1932
	,1927
	,1992
	,2097
	,2187
	,2242
	,2240
	,2185
	,2098
	,2003
	,1932
	,1927
	,1991
	,2094
	,2183
	,2241
	,2242
	,2187
	,2101
	,2006
	,1935
	,1927
	,1990
	,2093
	,2183
	,2241
	,2243
	,2189
	,2102
	,2007
	,1935
	,1928
	,1989
	,2091
	,2181
	,2237
	,2239
	,2186
	,2101
	,2006
	,1932
	,1919
	,1979
	,2082
	,2174
	,2234
	,2236
	,2186
	,2101
	,2006
	,1933
	,1922
	,1982
	,2087
	,2181
	,2242
	,2247
	,2198
	,2113
	,2017
	,1941
	,1928
	,1986
	,2090
	,2184
	,2245
	,2252
	,2203
	,2118
	,2022
	,1946
	,1932
	,1988
	,2089
	,2181
	,2241
	,2247
	,2199
	,2115
	,2020
	,1943
	,1928
	,1983
	,2084
	,2177
	,2240
	,2249
	,2201
	,2117
	,2020
	,1943
	,1927
	,1982
	,2083
	,2175
	,2239
	,2249
	,2201
	,2119
	,2024
	,1945
	,1926
	,1980
	,2080
	,2175
	,2238
	,2250
	,2203
	,2122
	,2025
	,1946
	,1926
	,1978
	,2080
	,2175
	,2238
	,2246
	,2188
	,2091
	,1979
	,1879
	,1837
	,1871
	,1962
	,2064
	,2152
	,2209
	,2236
	,2238
	,2219
	,2218
	,2269
	,2386
	,2562
	,2733
	,2870
	,2933
	,2905
	,2793
	,2630
	,2446
	,2313
	,2265
	,2279
	,2328
	,2369
	,2364
	,2306
	,2215
	,2108
	,2015
	,1976
	,2011
	,2100
	,2192
	,2254
	,2266
	,2220
	,2136
	,2037
	,1951
	,1923
	,1966
	,2062
	,2158
	,2226
	,2243
	,2202
	,2121
	,2024
	,1940
	,1910
	,1954
	,2051
	,2148
	,2219
	,2238
	,2197
	,2117
	,2022
	,1937
	,1909
	,1951
	,2047
	,2145
	,2213
	,2234
	,2194
	,2116
	,2021
	,1936
	,1906
	,1947
	,2044
	,2143
	,2213
	,2234
	,2196
	,2116
	,2022
	,1937
	,1904
	,1943
	,2037
	,2136
	,2206
	,2228
	,2193
	,2116
	,2020
	,1934
	,1900
	,1938
	,2033
	,2132
	,2203
	,2226
	,2190
	,2114
	,2018
	,1931
	,1897
	,1935
	,2030
	,2130
	,2201
	,2225
	,2190
	,2114
	,2018
	,1932
	,1895
	,1930
	,2022
	,2124
	,2197
	,2222
	,2189
	,2113
	,2016
	,1931
	,1893
	,1927
	,2020
	,2122
	,2196
	,2223
	,2192
	,2116
	,2021
	,1934
	,1896
	,1930
	,2025
	,2127
	,2201
	,2230
	,2199
	,2126
	,2031
	,1945
	,1904
	,1938
	,2031
	,2136
	,2211
	,2241
	,2212
	,2139
	,2047
	,1959
	,1918
	,1949
	,2041
	,2144
	,2221
	,2252
	,2221
	,2148
	,2055
	,1966
	,1922
	,1950
	,2041
	,2145
	,2221
	,2252
	,2223
	,2151
	,2056
	,1967
	,1923
	,1950
	,2040
	,2143
	,2220
	,2253
	,2225
	,2153
	,2060
	,1967
	,1921
	,1948
	,2038
	,2143
	,2219
	,2254
	,2228
	,2156
	,2061
	,1969
	,1922
	,1947
	,2035
	,2139
	,2216
	,2252
	,2227
	,2156
	,2063
	,1971
	,1922
	,1945
	,2033
	,2137
	,2214
	,2252
	,2227
	,2157
	,2062
	,1970
	,1920
	,1944
	,2031
	,2133
	,2213
	,2250
	,2227
	,2158
	,2065
	,1973
	,1923
	,1944
	,2029
	,2131
	,2210
	,2250
	,2228
	,2160
	,2067
	,1975
	,1922
	,1942
	,2027
	,2133
	,2212
	,2251
	,2232
	,2164
	,2071
	,1979
	,1925
	,1943
	,2029
	,2133
	,2213
	,2254
	,2235
	,2167
	,2075
	,1982
	,1928
	,1944
	,2026
	,2130
	,2211
	,2253
	,2235
	,2168
	,2077
	,1983
	,1928
	,1944
	,2024
	,2130
	,2212
	,2255
	,2238
	,2172
	,2081
	,1988
	,1930
	,1945
	,2024
	,2129
	,2212
	,2256
	,2240
	,2174
	,2083
	,1989
	,1933
	,1946
	,2025
	,2130
	,2212
	,2258
	,2243
	,2178
	,2088
	,1992
	,1933
	,1944
	,2023
	,2128
	,2212
	,2257
	,2244
	,2180
	,2090
	,1996
	,1935
	,1945
	,2023
	,2129
	,2212
	,2259
	,2246
	,2182
	,2091
	,1998
	,1937
	,1944
	,2022
	,2126
	,2211
	,2259
	,2247
	,2184
	,2095
	,1999
	,1938
	,1944
	,2019
	,2124
	,2209
	,2257
	,2247
	,2186
	,2096
	,2000
	,1938
	,1944
	,2017
	,2123
	,2209
	,2259
	,2248
	,2188
	,2098
	,2003
	,1940
	,1943
	,2016
	,2121
	,2207
	,2257
	,2249
	,2190
	,2101
	,2005
	,1940
	,1943
	,2014
	,2119
	,2206
	,2256
	,2248
	,2189
	,2100
	,2004
	,1937
	,1937
	,2007
	,2113
	,2201
	,2253
	,2246
	,2189
	,2101
	,2005
	,1939
	,1940
	,2009
	,2117
	,2206
	,2260
	,2256
	,2199
	,2112
	,2015
	,1947
	,1945
	,2014
	,2119
	,2207
	,2263
	,2259
	,2203
	,2115
	,2018
	,1948
	,1946
	,2013
	,2115
	,2204
	,2259
	,2256
	,2198
	,2111
	,2015
	,1946
	,1942
	,2007
	,2111
	,2201
	,2257
	,2257
	,2202
	,2115
	,2019
	,1948
	,1941
	,2005
	,2109
	,2200
	,2257
	,2257
	,2203
	,2118
	,2021
	,1947
	,1941
	,2005
	,2108
	,2198
	,2256
	,2258
	,2205
	,2119
	,2023
	,1949
	,1940
	,2003
	,2105
	,2198
	,2255
	,2251
	,2186
	,2085
	,1973
	,1879
	,1850
	,1894
	,1990
	,2090
	,2171
	,2221
	,2243
	,2238
	,2219
	,2225
	,2284
	,2412
	,2593
	,2761
	,2889
	,2942
	,2901
	,2780
	,2613
	,2432
	,2311
	,2274
	,2296
	,2346
	,2382
	,2370
	,2307
	,2211
	,2104
	,2015
	,1988
	,2034
	,2128
	,2215
	,2272
	,2276
	,2223
	,2136
	,2037
	,1958
	,1941
	,1992
	,2093
	,2185
	,2247
	,2254
	,2205
	,2121
	,2025
	,1947
	,1929
	,1982
	,2083
	,2177
	,2240
	,2250
	,2202
	,2121
	,2025
	,1946
	,1927
	,1979
	,2077
	,2172
	,2236
	,2247
	,2200
	,2120
	,2027
	,1947
	,1925
	,1975
	,2075
	,2170
	,2234
	,2247
	,2201
	,2120
	,2024
	,1945
	,1923
	,1972
	,2072
	,2167
	,2230
	,2244
	,2200
	,2118
	,2024
	,1942
	,1918
	,1967
	,2068
	,2164
	,2229
	,2243
	,2200
	,2119
	,2023
	,1943
	,1918
	,1965
	,2063
	,2160
	,2226
	,2242
	,2198
	,2119
	,2024
	,1942
	,1916
	,1962
	,2059
	,2155
	,2222
	,2239
	,2197
	,2118
	,2024
	,1942
	,1915
	,1960
	,2056
	,2155
	,2223
	,2242
	,2203
	,2125
	,2031
	,1947
	,1919
	,1964
	,2061
	,2159
	,2228
	,2248
	,2210
	,2134
	,2039
	,1957
	,1929
	,1972
	,2068
	,2167
	,2237
	,2258
	,2220
	,2146
	,2053
	,1968
	,1938
	,1980
	,2074
	,2172
	,2242
	,2264
	,2227
	,2151
	,2057
	,1972
	,1941
	,1979
	,2074
	,2172
	,2242
	,2266
	,2229
	,2153
	,2060
	,1975
	,1941
	,1978
	,2072
	,2170
	,2241
	,2265
	,2229
	,2154
	,2062
	,1975
	,1940
	,1977
	,2071
	,2170
	,2241
	,2266
	,2231
	,2156
	,2063
	,1976
	,1940
	,1976
	,2068
	,2167
	,2238
	,2264
	,2229
	,2155
	,2064
	,1977
	,1941
	,1974
	,2064
	,2163
	,2235
	,2262
	,2230
	,2156
	,2063
	,1976
	,1938
	,1971
	,2062
	,2161
	,2233
	,2261
	,2230
	,2158
	,2066
	,1979
	,1939
	,1969
	,2059
	,2158
	,2231
	,2260
	,2231
	,2159
	,2067
	,1980
	,1939
	,1967
	,2056
	,2157
	,2231
	,2261
	,2233
	,2162
	,2072
	,1984
	,1942
	,1970
	,2058
	,2159
	,2232
	,2264
	,2236
	,2165
	,2074
	,1986
	,1943
	,1969
	,2057
	,2157
	,2232
	,2264
	,2238
	,2168
	,2076
	,1988
	,1944
	,1969
	,2053
	,2154
	,2229
	,2263
	,2239
	,2170
	,2079
	,1990
	,1945
	,1968
	,2052
	,2153
	,2230
	,2263
	,2239
	,2170
	,2079
	,1992
	,1945
	,1966
	,2051
	,2152
	,2228
	,2264
	,2241
	,2174
	,2084
	,1995
	,1947
	,1968
	,2050
	,2152
	,2230
	,2265
	,2244
	,2178
	,2089
	,1998
	,1949
	,1968
	,2050
	,2152
	,2229
	,2268
	,2246
	,2179
	,2090
	,1999
	,1951
	,1968
	,2049
	,2150
	,2228
	,2266
	,2247
	,2181
	,2092
	,2002
	,1950
	,1967
	,2047
	,2147
	,2226
	,2266
	,2248
	,2183
	,2095
	,2006
	,1952
	,1968
	,2047
	,2148
	,2226
	,2265
	,2249
	,2184
	,2095
	,2007
	,1954
	,1968
	,2045
	,2146
	,2223
	,2264
	,2248
	,2185
	,2096
	,2005
	,1949
	,1963
	,2041
	,2141
	,2220
	,2262
	,2248
	,2185
	,2097
	,2010
	,1954
	,1965
	,2043
	,2146
	,2226
	,2270
	,2255
	,2195
	,2107
	,2017
	,1960
	,1969
	,2046
	,2148
	,2228
	,2275
	,2261
	,2200
	,2112
	,2021
	,1962
	,1970
	,2041
	,2141
	,2222
	,2268
	,2256
	,2196
	,2109
	,2018
	,1961
	,1969
	,2040
	,2141
	,2222
	,2268
	,2257
	,2198
	,2113
	,2021
	,1961
	,1967
	,2037
	,2137
	,2219
	,2268
	,2257
	,2199
	,2113
	,2023
	,1962
	,1965
	,2036
	,2136
	,2218
	,2267
	,2257
	,2199
	,2115
	,2025
	,1962
	,1966
	,2035
	,2135
	,2215
	,2255
	,2235
	,2163
	,2060
	,1951
	,1872
	,1863
	,1930
	,2040
	,2149
	,2248
	,2308
	,2318
	,2302
	,2286
	,2286
	,2356
	,2500
	,2669
	,2820
	,2909
	,2897
	,2794
	,2619
	,2424
	,2266
	,2183
	,2198
	,2271
	,2333
	,2368
	,2349
	,2283
	,2189
	,2089
	,2013
	,2000
	,2056
	,2150
	,2229
	,2277
	,2270
	,2214
	,2128
	,2034
	,1965
	,1960
	,2021
	,2120
	,2204
	,2257
	,2255
	,2201
	,2117
	,2025
	,1959
	,1953
	,2013
	,2112
	,2198
	,2251
	,2251
	,2200
	,2116
	,2026
	,1957
	,1950
	,2010
	,2109
	,2195
	,2250
	,2249
	,2198
	,2117
	,2027
	,1957
	,1947
	,2007
	,2107
	,2194
	,2249
	,2251
	,2199
	,2118
	,2027
	,1957
	,1947
	,2005
	,2103
	,2190
	,2246
	,2249
	,2200
	,2119
	,2028
	,1958
	,1947
	,2005
	,2103
	,2190
	,2248
	,2252
	,2202
	,2122
	,2031
	,1958
	,1946
	,2003
	,2101
	,2190
	,2246
	,2251
	,2203
	,2123
	,2031
	,1960
	,1946
	,2002
	,2099
	,2187
	,2246
	,2254
	,2207
	,2128
	,2038
	,1966
	,1951
	,2004
	,2102
	,2193
	,2252
	,2261
	,2216
	,2137
	,2046
	,1973
	,1958
	,2010
	,2107
	,2197
	,2259
	,2269
	,2225
	,2146
	,2056
	,1982
	,1965
	,2016
	,2113
	,2204
	,2265
	,2275
	,2230
	,2150
	,2060
	,1983
	,1963
	,2012
	,2107
	,2197
	,2258
	,2269
	,2224
	,2146
	,2054
	,1977
	,1956
	,2005
	,2101
	,2191
	,2254
	,2266
	,2223
	,2146
	,2054
	,1978
	,1956
	,2003
	,2097
	,2189
	,2252
	,2267
	,2224
	,2146
	,2054
	,1979
	,1956
	,2001
	,2095
	,2187
	,2252
	,2266
	,2223
	,2147
	,2056
	,1977
	,1953
	,1998
	,2093
	,2185
	,2249
	,2265
	,2225
	,2149
	,2058
	,1979
	,1952
	,1996
	,2090
	,2183
	,2246
	,2264
	,2225
	,2149
	,2058
	,1979
	,1952
	,1994
	,2086
	,2181
	,2246
	,2263
	,2227
	,2152
	,2060
	,1981
	,1954
	,1995
	,2087
	,2182
	,2248
	,2266
	,2228
	,2153
	,2063
	,1982
	,1953
	,1993
	,2085
	,2181
	,2248
	,2267
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Para_Init();

	//serial port control
	connect(this->ui->port_name_Comb,SIGNAL(currentIndexChanged(const QString)),this,SLOT(sel_portName(QString)));
	connect(this->ui->baud_rate_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_BaudRate(int)));
	connect(this->ui->stop_bits_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_stopBits(int)));
	connect(this->ui->data_bits_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_dataBits(int)));
	connect(this->ui->parity_Comb,   SIGNAL(currentIndexChanged(int)),			this,SLOT(set_Parity(int)));
	connect(this->ui->open_port_Btn, SIGNAL(clicked()),							this,SLOT(open_Port()));
	connect(this->ui->close_port_Btn,SIGNAL(clicked()),							this,SLOT(close_Port()));
	connect(this->ui->send_Btn,		 SIGNAL(clicked()),							this,SLOT(send_Data()));
	
	//filters
	connect(this->ui->refresh_Time,  SIGNAL(valueChanged(int)),				this,SLOT(get_refresh_Timeout(int)));
	connect(this->ui->filter_Combo,  SIGNAL(currentIndexChanged(int)),		this,SLOT(set_Filter(int)));
	connect(this->ui->leve_In,		 SIGNAL(valueChanged(int)),				this,SLOT(set_Level(int)));

	//connect timer function
	connect(this->check_port_Timer,SIGNAL(timeout()),this,SLOT(check_port_Status()));
	//connect(this->test_timer,      SIGNAL(timeout()),this,SLOT(test_timer_func()));
	//com port receive data signal has already connected in open_port()
	//connect signal to enable atuo-scroll in info panel
	connect(this->ui->info_Panel,SIGNAL(cursorPositionChanged()),this,SLOT(info_Panel_Scroll()));
	//connect user defined function
	connect(this,SIGNAL(get_data_Done(double)),this,SLOT(pass_Dot(double)));
	//connect sliderbar
	connect(this->ui->num_points_Slider,SIGNAL(valueChanged(int)),this,SLOT(change_X_Scope(int)));
	connect(this->ui->y_pos_Scope,SIGNAL(valueChanged(int)),this,SLOT(change_Y_pos_Scope(int)));
	connect(this->ui->y_neg_Scope,SIGNAL(valueChanged(int)),this,SLOT(change_Y_neg_Scope(int)));

	//connect screen shot and save data function
	connect(this->ui->screen_shot_Btn,SIGNAL(clicked()),this,SLOT(snip_Screen()));
	connect(this->ui->save_data_Btn,  SIGNAL(toggled(bool)),this,SLOT(check_save_Data(bool)));
	
}

MainWindow::~MainWindow()
{
	//stop timer first
	check_port_Timer->stop();
	delete check_port_Timer;

	if (myCom!=NULL)
	{
		delete myCom;
	}

	delete plot_view;
}



void MainWindow::Para_Init()
{
	point_cnt = 100;
	plot_view = new QwtPlotView(this->ui->qwtPlot);

	check_port_Timer = new QTimer(this);
	test_timer = new QTimer(this);
	test_timer->start(2);
	test_timer_cnt = 0;
	this->data_text = NULL;

	//start timer here
	check_port_Timer->start(500);
	this->ui->refresh_Time->setRange(0,1000);
	this->ui->refresh_Time->setValue(10);

	comName = "com1";
	myComSetting.BaudRate = BAUD9600;
	myComSetting.DataBits = DATA_8;
	myComSetting.Parity   = PAR_NONE;
	myComSetting.FlowControl = FLOW_OFF;
	myComSetting.StopBits = STOP_1;
	myComSetting.Timeout_Millisec = 50;

	myCom = NULL;//new Win_QextSerialPort(comName,myComSetting,QextSerialBase::EventDriven);

	//setup slider bar
	this->ui->num_points_Slider->setMinimum(100);
	this->ui->num_points_Slider->setMaximum(2000);
	this->ui->num_points_Slider->setTickInterval(100);

	//setup y scope bar
	this->ui->y_pos_Scope->setMinimum(-100);
	this->ui->y_pos_Scope->setMaximum(2000);
	this->ui->y_pos_Scope->setSliderPosition(2);
	this->ui->y_neg_Scope->setMinimum(-2000);
	this->ui->y_neg_Scope->setMaximum(100);
	this->ui->y_neg_Scope->setSliderPosition(-2);

	//filter ui
	this->ui->leve_In->setValue(5);
	this->ui->leve_In->setMaximum(10);
	this->ui->leve_In->setMinimum(1);
	this->ui->filter_Combo->setCurrentIndex(0);

	//--------------init signal process parameters------------//
	long_length = 100;
	signal_len = SIGNAL_LEN;
	memset(signal_init,0,signal_len*sizeof(double));
	de_level = 5;
	filter_name = 0;
	memset(coeff,0,10*sizeof(WaveCoeff));
	memset(recon,0,10*sizeof(WaveCoeff));
}

//receive data and do wavelet decompose and reconstruct 
//emit a signal and pass data to plot in chart view
void MainWindow::receive_Data()
{
	if (myCom->bytesAvailable()>=10)
	{
		QByteArray temp = myCom->readAll();
		com_temp.append(temp);
		while (com_temp.contains("a"))
		{
			QByteArray right_temp = com_temp.left(com_temp.indexOf("a"));
			com_temp.remove(0,right_temp.size()+1);
			double tem_num = right_temp.toDouble();
			//this->ui->info_Panel->insertPlainText(QString::number(tem_num));
			//this->ui->info_Panel->insertPlainText("\n");
			//this line emit a signal to trigger pass_Dot
			emit get_data_Done(tem_num);
		}
	}
}


//trigger by receive_data 
//pass data to buff
void MainWindow::pass_Dot(double in_data)
{
	double means = 0.0;
	//process data first
	for (int j=0;j<signal_len-1;j++)
	{
		signal_init[j] = signal_init[j+1];
		means = means+signal_init[j+1];
	}

	signal_init[signal_len-1] = in_data;
	means = means+in_data;
	means = means/signal_len;

	//de-means
	for (int j=0;j<signal_len;j++)
	{
		//signal_init[j] =signal_init[j]-means; 
	}

	if (this->ui->en_filter_Btn->isChecked())
	{
		//----------do transform---------------//
		switch(filter_name)
		{
		case 0: //db4
			{
				WaveDecompose(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
				break;
			}
		case 1: //db5
			{
				WaveDecompose(signal_init,signal_len,db5_Lo_D,db5_len,db4_Hi_D,db5_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,db5_Lo_R,db5_len,db4_Hi_R,db5_len,coeff,recon,'a',de_level);
				break;
			}
		case 2: //db6
			{
				WaveDecompose(signal_init,signal_len,db6_Lo_D,db6_len,db6_Hi_D,db6_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,db6_Lo_R,db6_len,db6_Hi_R,db6_len,coeff,recon,'a',de_level);
				break;
			}
		case 3: //sym4
			{
				WaveDecompose(signal_init,signal_len,sym4_Lo_D,sym4_len,sym4_Hi_D,sym4_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,sym4_Lo_R,sym4_len,sym4_Hi_R,sym4_len,coeff,recon,'a',de_level);
				break;
			}
		case 4: //sym5
			{
				WaveDecompose(signal_init,signal_len,sym5_Lo_D,sym5_len,sym5_Hi_D,sym5_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,sym5_Lo_R,sym5_len,sym5_Hi_R,sym5_len,coeff,recon,'a',de_level);
				break;
			}
		case 5: //sym6
			{
				WaveDecompose(signal_init,signal_len,sym6_Lo_D,sym6_len,sym6_Hi_D,sym6_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,sym6_Lo_R,sym6_len,sym6_Hi_R,sym6_len,coeff,recon,'a',de_level);
				break;
			}
		case 6: //coif4
			{
				WaveDecompose(signal_init,signal_len,coif4_Lo_D,coif4_len,coif4_Hi_D,coif4_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,coif4_Lo_R,coif4_len,coif4_Hi_R,coif4_len,coeff,recon,'a',de_level);
				break;
			}
		case 7: //coif5
			{
				WaveDecompose(signal_init,signal_len,coif5_Lo_D,coif5_len,coif5_Hi_D,coif5_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,coif5_Lo_R,coif5_len,coif5_Hi_R,coif5_len,coeff,recon,'a',de_level);
				break;
			}
		default: //db4
			{
				WaveDecompose(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
				WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
				break;
			}
		}
		means = 0;
		for (int j=0;j<signal_len;j++)
		{
			means = means+signal_init[j]; 
		}
		//std::cout<<recon[0].capp[signal_len-10]<<std::endl;
		this->plot_view->pass_Dot(recon[0].capp[signal_len-10]-means/signal_len);
	}
	else
	{
		this->plot_view->pass_Dot(signal_init[signal_len-1]);
	}
	//std::cout<<in_data<<std::endl;
}

void MainWindow::send_Data()
{
	if (myCom == NULL)
		return;
	else
	{
		if (!myCom->isOpen())
		{
			QMessageBox::warning(NULL,"warning","Com Port no open",QMessageBox::Yes);
			return;
		}
	}

	QString temp = this->ui->send_Panel->toPlainText();

	//send data
	myCom->write(temp.toAscii());

	//clear data in send panel
	this->ui->send_Panel->clear();
}


void MainWindow::find_Port()
{
	//myCom->close();
}


void MainWindow::open_Port()
{
	//create new com port
	if (myCom != NULL)
	{
		disconnect(myCom,SIGNAL(readyRead()),this,SLOT(receive_Data()));
		delete myCom;
	}
	myCom = new Win_QextSerialPort(comName,myComSetting,QextSerialBase::EventDriven);

	//open it
	if (!myCom->open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(NULL,"Warning","Cannot Open Port",QMessageBox::Yes);
		return;
	}

	//
	connect(myCom,SIGNAL(readyRead()),this,SLOT(receive_Data()));
}

void MainWindow::close_Port()
{
	if (myCom == NULL)
	{
		return;
	}
	if (myCom->isOpen())
	{
		myCom->close();
	}
}

void MainWindow::sel_portName(QString str)
{
	std::cout<<str.toStdString()<<std::endl;
	comName = str;
}

void MainWindow::set_BaudRate(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.BaudRate = BAUD9600;
			break;
		}
	case 1:
		{
			myComSetting.BaudRate = BAUD19200;
			break;
		}
	case 2:
		{
			myComSetting.BaudRate = BAUD115200;
			break;
		}
	case 3:
		{
			myComSetting.BaudRate = BAUD300;
			break;
		}
	case 4:
		{
			myComSetting.BaudRate = BAUD600;
			break;
		}
	case 5:
		{
			myComSetting.BaudRate = BAUD1200;
			break;
		}
	case 6:
		{
			myComSetting.BaudRate = BAUD2400;
			break;
		}
	case 7:
		{
			myComSetting.BaudRate = BAUD4800;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_Parity(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.Parity = PAR_NONE;
			break;
		}
	case 1:
		{
			myComSetting.Parity = PAR_ODD;
			break;
		}
	case 2:
		{
			myComSetting.Parity = PAR_EVEN;
			break;
		}
	case 3:
		{
			myComSetting.Parity = PAR_MARK;
			break;
		}
	case 4:
		{
			myComSetting.Parity = PAR_SPACE;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_dataBits(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.DataBits = DATA_8;
			break;
		}
	case 1:
		{
			myComSetting.DataBits = DATA_7;
			break;
		}
	case 2:
		{
			myComSetting.DataBits = DATA_6;
			break;
		}
	case 3:
		{
			myComSetting.DataBits = DATA_5;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_stopBits(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.StopBits = STOP_1;
			break;
		}
	case 1:
		{
			myComSetting.StopBits = STOP_2;
			break;
		}
	case 2:
		{
			myComSetting.StopBits = STOP_1_5;
			break;
		}
	default:
		break;
	}
}

//information scroll in info panel
void MainWindow::info_Panel_Scroll()
{
	QTextCursor text_cursor =  ui->info_Panel->textCursor();
	text_cursor.movePosition(QTextCursor::End);
	ui->info_Panel->setTextCursor(text_cursor);
}

void MainWindow::get_refresh_Timeout(int in)
{
	plot_view->setInterval(in);
}

void MainWindow::check_port_Status()
{
	if (myCom == NULL)
	{
		this->ui->is_Open_Btn->setChecked(Qt::Unchecked);
	}
	else
	{
		if (myCom->isOpen())
		{
			this->ui->is_Open_Btn->setChecked(Qt::Checked);
		}
		else
		{
			this->ui->is_Open_Btn->setChecked(Qt::Unchecked);
		}
	}
	return;
}

void MainWindow::change_X_Scope(int num)
{
	plot_view->change_X_Scope(num);
}

void MainWindow::change_Y_pos_Scope(int pos)
{
	plot_view->change_Y_Scope(pos,this->ui->y_neg_Scope->value());
}

void MainWindow::change_Y_neg_Scope(int neg)
{
	plot_view->change_Y_Scope(this->ui->y_pos_Scope->value(),neg);
}

void MainWindow::test_timer_func()
{
	if (test_timer_cnt>3300)
	{
		test_timer_cnt = 0;
	}
	//double pi = 3.1415926;
	double data_buff = test_data[test_timer_cnt];
	test_timer_cnt++;

	emit get_data_Done(data_buff);

}

void MainWindow::set_Filter(int index)
{
	filter_name = index;
}

void MainWindow::set_Level(int index)
{
	de_level = index;
}

void MainWindow::check_save_Data(bool checked)
{
	if (checked)
	{
		QString filename_data = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
		filename_data.append(".txt");
		this->data_file.setFileName(filename_data);
		if (this->data_file.isOpen())
			this->data_text = new QTextStream(&data_file);
		else if (data_file.open(QFile::WriteOnly)| (QIODevice::Text))
			this->data_text = new QTextStream(&data_file);

		//disconnect signal and re-connect
		//disconnect(this,SIGNAL(get_data_Done(double)),this,SLOT(pass_Dot(double)));
		connect(this,SIGNAL(get_data_Done(double)),this,SLOT(save_Dot(double)));
	}
	
	else
	{
		qDebug()<<"not checked";
		disconnect(this,SIGNAL(get_data_Done(double)),this,SLOT(save_Dot(double)));
		//connect(this,SIGNAL(get_data_Done(double)),this,SLOT(pass_Dot(double)));

		if (this->data_text == NULL)
		{
			return;
		}
		else
		{
			data_file.close();
			delete this->data_text;
			this->data_text = NULL;
		}
	}
}
void MainWindow::save_Dot(double num)
{
	if (this->data_text == NULL)
	{
		return;	
	}
	else
	{
		*(this->data_text)<<num<<endl;
	}
}
void MainWindow::snip_Screen()
{
	QPixmap screen;
	QString format = "PNG";
	QString filename_screen = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	filename_screen.append(".png");
	screen = QPixmap::grabWidget(this->ui->plot_widget);
	screen.save(filename_screen,"PNG");
}


QwtPlotView::QwtPlotView(QwtPlot* plot)
{
	this->plot_view = plot;
	//plot init process
	this->plot_view->setTitle( "ECG Signal" );
	this->plot_view->setCanvasBackground( Qt::white );
	this->plot_view->setAxisScale( QwtPlot::yLeft, -2.0, 2.0 );
	this->plot_view->setAxisScale( QwtPlot::xBottom, 0.0, 100.0 );
	this->plot_view->insertLegend( new QwtLegend() );

	grid = new QwtPlotGrid();
	grid->attach( this->plot_view);

	curve = new QwtPlotCurve();
	//curve->setTitle( "Some Points" );
	curve->setPen( Qt::blue, 2 ),
		curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
	//curve->setSymbol( symbol );

	curve->attach( this->plot_view);

	num_points_dis = 100;
	//init points here
	point_coor.length = num_points_dis;
	point_coor.x_val = new double[point_coor.length];
	point_coor.y_val = new double[point_coor.length];
	for (int i=0;i<point_coor.length;i++)
	{
		point_coor.x_val[i]=i;
		point_coor.y_val[i]=0;
	}
	dot_temp = 0.0;
	point_cnt = 0;

	curve->setRawSamples(point_coor.x_val,point_coor.y_val,point_coor.length);

	timer_plot = new QTimer;
	timer_plot->start(1);
	//connect 
	connect(timer_plot,SIGNAL(timeout()),this,SLOT(run()));
}

QwtPlotView::~QwtPlotView()
{
	//disconnect
	this->exit();
	disconnect(timer_plot,SIGNAL(timeout()),this,SLOT(run()));
	//stop timer
	timer_plot->stop();
	delete timer_plot;

	delete curve;
	delete grid;
	delete symbol;

	delete point_coor.x_val;
	delete point_coor.y_val;
}

void QwtPlotView::replot(QPolygonF* new_points)
{
	curve->setSamples( *new_points );
	this->plot_view->replot();
}

//inter refresh frequency
void QwtPlotView::setInterval(int inter)
{
	timer_plot->start(inter);
}

void QwtPlotView::run()
{
	if (point_cnt>this->num_points_dis-1)
	{
		point_cnt = 0;
	}
	point_coor.y_val[point_cnt] = dot_temp;
	point_cnt++;

	this->plot_view->replot();
}

void QwtPlotView::pass_Dot(double d)
{
	dot_temp = d;
}

void QwtPlotView::change_Y_Scope(int pos,int neg)
{
	this->plot_view->setAxisScale( QwtPlot::yLeft,neg ,pos  );
}

void QwtPlotView::change_X_Scope(int xx)
{
	this->num_points_dis = xx;
	point_coor.length = num_points_dis;
	//delete data first
	delete point_coor.x_val;
	delete point_coor.y_val;

	//re-new array
	point_coor.x_val = new double[point_coor.length];
	point_coor.y_val = new double[point_coor.length];
	for (int i=0;i<point_coor.length;i++)
	{
		point_coor.x_val[i]=i;
		point_coor.y_val[i]=0;
	}

	this->plot_view->setAxisScale( QwtPlot::xBottom, 0.0, point_coor.length );
	curve->setRawSamples(point_coor.x_val,point_coor.y_val,point_coor.length);
}



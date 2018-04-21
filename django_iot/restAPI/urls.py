from django.urls import path, include
from rest_framework.urlpatterns import format_suffix_patterns
from restAPI import views

urlpatterns = [
	path('', views.PostList.as_view()),
	#regardless to the detail
	path('<int:pk>/', views.PostDetail.as_view()),
	path('index', views.app),
	path('arduino', views.get_data_from_arduino)
]

urlpatterns = format_suffix_patterns(urlpatterns)
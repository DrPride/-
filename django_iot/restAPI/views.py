from restAPI.models import Post
from restAPI.serializers import restAPISerializer
from rest_framework import generics
from django.shortcuts import render, render_to_response
from django.http import HttpResponse

def app(request):
	return render_to_response('index.html')

class PostList(generics.ListCreateAPIView):
    queryset = Post.objects.all()
    serializer_class = restAPISerializer


class PostDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Post.objects.all()
    serializer_class = restAPISerializer
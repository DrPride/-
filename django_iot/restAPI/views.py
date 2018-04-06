from restAPI.models import Post
from restAPI.serializers import restAPISerializer
from rest_framework import generics


class PostList(generics.ListCreateAPIView):
    queryset = Post.objects.all()
    serializer_class = restAPISerializer


class PostDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Post.objects.all()
    serializer_class = restAPISerializer
from rest_framework import serializers
from restAPI.models import Post

class restAPISerializer(serializers.ModelSerializer):
    # realize the Create and Update Methods
    class Meta:
        model = Post
        # HyperLinkedxx make the url
        fields = ('id', 'created','led13', 'temperature', 'sensors1', 'sensors2')
    

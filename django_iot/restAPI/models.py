from django.db import models

# Create your models here.
class Post(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    led13 = models.BooleanField(default = False)
    temperature = models.FloatField(default = True)
    sensors1 = models.FloatField(default = True)
    sensors2 = models.FloatField(default = True)
    class Meta:
        ordering = ('created',)


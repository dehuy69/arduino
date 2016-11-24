from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

# Create your views here.
@csrf_exempt
def recognize(request):
    if request.method == 'POST':
        user = request.POST.get('username')
        password = request.POST.get('password')
        return HttpResponse("Username: " +user +"Password: " +password)
    if request.method == 'GET':
        return HttpResponse("hello world")

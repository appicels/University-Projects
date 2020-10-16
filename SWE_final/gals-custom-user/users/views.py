from django.shortcuts import render, redirect
from .forms import CustomUserCreationForm
#from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.views import generic
from django.views import View
from django.views.generic import TemplateView

from django.urls import reverse
from django.views.generic import TemplateView, DetailView
from django.views.generic.edit import CreateView, UpdateView
from dynamic_forms.views import DynamicFormMixin
from .models import Survey, SurveyResponse

from django.http import HttpResponse
from .models import Course
from .models import CourseStudent
from django import forms
from django.db import models
from .forms import CreateClass
import xlwt
from dynamic_forms.models import FormField, ResponseField
#kyle 1
# from .myForm import myForm

# #kyle 2
# from django.http import HttpResponse
# #from .forms import CreatePollForm
# from .models import Poll


class SignUp(generic.CreateView):
    #form_class = UserCreationForm
    form_class = CustomUserCreationForm

    #register(CustomUser, CustomUserAdmin)
    success_url = reverse_lazy('login')
    template_name = 'signup.html'

class Initial(TemplateView):
    template_name = 'initial.html'



class IndexView(TemplateView):
    template_name = "index.html"

    def get_context_data(self, *args, **kwargs):
        context = super().get_context_data(*args, **kwargs)
        context['surveys'] = Survey.objects.all()
        return context

class ResponsiveView(TemplateView):
    template_name = "responding.html"

    def get_context_data(self, *args, **kwargs):
        context = super().get_context_data(*args, **kwargs)
        context['surveys'] = Survey.objects.all()
        return context
  
class BuildView(CreateView):
    model = Survey
    fields = '__all__'
    template_name = "build.html"
    def get_success_url(self):
        return reverse('survey_creation_success')


class SuccessView(TemplateView):
    template_name = "survey_creation_success.html"


class SurveyDetailView(DetailView):
    model = Survey
    pk_url_kwarg = "survey_id"
    template_name = "survey_detail.html"

class SurveyDetailViewStudent(DetailView):
    model = Survey
    pk_url_kwarg = "survey_id"
    template_name = "survey_detail_student.html"

class SurveyEditView(UpdateView):
    model = Survey
    fields = '__all__'
    pk_url_kwarg = "survey_id"
    template_name = "survey_edit.html"

    def get_success_url(self):
        return reverse('survey_detail', kwargs={"survey_id": self.object.pk})


class RespondView(DynamicFormMixin, CreateView):
    model = SurveyResponse
    fields = ['response']
    template_name = "respond.html"

    form_model = Survey
    form_pk_url_kwarg = "survey_id"
    response_form_fk_field = "survey"
    response_field = "response"

    def get_success_url(self):
        return reverse('survey_detail_student', kwargs={"survey_id": self.form_instance.pk})

def export_users_xls(request):
    response = HttpResponse(content_type='application/ms-excel')
    response['Content-Disposition'] = 'attachment; filename="ThePythonDjango.xls"'
    wb = xlwt.Workbook(encoding='utf-8')
    ws = wb.add_sheet("sheet1")
    row_num = 0
    font_style = xlwt.XFStyle()
    font_style.font.bold = True
    sauce = SurveyResponse.objects.all()
    hockey = len(sauce)
    columns = []
    for i in range(1,hockey+1):
        stop = 'Response'
        columns.append(stop + str(i))
    for col_num in range(len(columns)):
         ws.write(row_num, col_num, columns[col_num], font_style)
    font_style = xlwt.XFStyle()
    j = 0

    for i in range(3,hockey+1):
        print(i)
        data = SurveyResponse.objects.get(id = i)
        row_num = row_num + 1
        hockeytwo = str(data.response)
        print(hockeytwo)
        ws.write(row_num, j, hockeytwo, font_style)
        j+=1
    wb.save(response)
    return response




def Class(request):
    if request.method == 'POST':
        form = CreateClass(request.POST)
        if form.is_valid():
            form.save()
            return redirect('home')
    else:
        form = CreateClass()
    context = {
       'form' : form
    }
    return render(request, 'create_class.html', context)

def homekyle(request):
    courses = Course.objects.all()
    context = {
       'courses' : courses
    }
    return render(request, 'home.html', context)


def selectedCourse(request):
    data = request.POST.get('hockey', False)
    sauce = len(Survey.objects.all())
    bb = Survey.objects.filter(topic = data)
    return render(request, 'filtered.html', {'data':bb})

def selectedCourseStudent(request):
    data = request.POST.get('hockey', False)
    sauce = len(Survey.objects.all())
    bb = Survey.objects.filter(topic = data)
    return render(request, 'filteredStudent.html', {'data':bb})


        

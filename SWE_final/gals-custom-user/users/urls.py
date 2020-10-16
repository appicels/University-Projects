# accounts/urls.py
from django.urls import path

from . import views
from django.views.generic import TemplateView
from django.conf import settings
from django.conf.urls import include, url


urlpatterns = [
    path('signup/', views.SignUp.as_view(), name='signup'),
    path('initial/', TemplateView.as_view(template_name = "initial.html"), name = 'initial'),
    path('survey/index/', views.IndexView.as_view(), name="index"),
    path('survey/responsive/', views.ResponsiveView.as_view(), name="respond"),
    path('survey/new/', views.BuildView.as_view(), name="survey_create"),
    path('survey/new/creation-success/', views.SuccessView.as_view(), name="survey_creation_success"),
    path('survey/<int:survey_id>/', views.SurveyDetailView.as_view(), name="survey_detail"),
    path('surveystudent/<int:survey_id>/', views.SurveyDetailViewStudent.as_view(), name="survey_detail_student"),
    path('survey/<int:survey_id>/edit/', views.SurveyEditView.as_view(), name="survey_edit"),
    path('survey/<int:survey_id>/response/', views.RespondView.as_view(), name="survey_respond"),
    path('survey/<int:survey_id>/response/<int:response_id>/', views.RespondView.as_view(), name="response"),
    path('home/create_class/', views.Class, name='create_class'),
    path('accounts/home/', views.homekyle, name='home'),
    #path('home/reg_class/', views.regClass, name='reg_class')
   # path('accounts/home/reg_class/', views.regClass, name='reg_class'),
    path('survey/export/xls/$', views.export_users_xls, name='export_users_xls'),
    path('filtered/', views.selectedCourse, name='selectedCourse'),
    path('filteredStudent/', views.selectedCourseStudent, name='selectedCourseStudent'),
    
]

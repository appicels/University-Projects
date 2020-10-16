from django.contrib import admin

# Register your models here.
from django.contrib import admin
from django.contrib.auth.admin import UserAdmin

from .forms import CustomUserCreationForm, CustomUserChangeForm
from .models import CustomUser, Course
#, Course, CourseTeam, CourseStudent, CourseInstructor, Assessment, AssessmentOEQ

from django import forms
from django.contrib.auth import get_user_model
from django.contrib.admin.widgets import FilteredSelectMultiple
from django.contrib.auth.models import Group


class CustomUserAdmin(UserAdmin):
    add_form = CustomUserCreationForm
    form = CustomUserChangeForm
    model = CustomUser
    list_display = ('email', 'is_staff', 'is_active', 'is_instructor',)
    list_filter = ('email', 'is_staff', 'is_active', 'is_instructor',)
    fieldsets = (
        (None, {'fields': ('email', 'password')}),
        ('Permissions', {'fields': ('is_staff', 'is_active')}),
    )
    add_fieldsets = (
        (None, {
            'classes': ('wide',),
            'fields': ('first_name', 'last_name', 'eagle_id','email', 'password1', 'password2','is_instructor', 'is_staff', 'is_active')}
        ),
    )
    search_fields = ('email',)
    ordering = ('email',)

class CourseAdmin(admin.ModelAdmin):
    #add_form = CourseAddForm
    #form = CourseAddForm
    model = Course
    list_display = ('course_name', 'course_id', 'course_date', 'course_section', 'course_semester',)
    search_fields = ('course_name',)
    ordering = ('course_name',)



admin.site.register(CustomUser, CustomUserAdmin)
admin.site.register(Course, CourseAdmin)

#admin.site.register(Course)
# admin.site.register(CourseInstructor)
# admin.site.register(CourseTeam)
# admin.site.register(CourseStudent)
# admin.site.register(Assessment)
# admin.site.register(AssessmentOEQ)
